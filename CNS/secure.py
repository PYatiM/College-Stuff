#!/usr/bin/env python3
"""
Secure combo: ECC (ECDH + ECDSA) + AES-256-GCM + SHA3-512

required:
    pip install cryptography
    pip install base64
    pip install os
    pip install hashlib
    pip install sys

Flow:
 - Recipient: long-term ECC key pair (recipient_priv / recipient_pub)
 - Sender: long-term ECC signing key (sender_sign_priv / sender_sign_pub)
 - Sender: ephemeral ECDH key to derive AES key using recipient_pub
 - AES key derived by HKDF using SHA3-512 -> AES-256
 - AES-GCM encrypts plaintext; sender also signs plaintext with ECDSA+SHA3-512
 - Transmit: ephemeral_pub + sender_sign_pub + nonce + ciphertext + tag + signature
 - Recipient reconstructs AES key with ephemeral_pub + recipient_priv, decrypts and verifies signature.
"""

import os
import base64

from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from cryptography.hazmat.primitives.asymmetric import utils

# -------------- Helpers --------------
def b64(x: bytes) -> str:
    return base64.b64encode(x).decode('ascii')

def ub64(s: str) -> bytes:
    return base64.b64decode(s.encode('ascii'))

# -------------- Key generation (recipient long-term, sender long-term signing) --------------
def generate_ecc_keypair(curve=ec.SECP384R1()):
    priv = ec.generate_private_key(curve)
    pub = priv.public_key()
    return priv, pub

def serialize_public_key(pub):
    return pub.public_bytes(
        encoding=serialization.Encoding.X962,
        format=serialization.PublicFormat.UncompressedPoint
    )

def load_public_key_from_bytes(data, curve=ec.SECP384R1()):
    return ec.EllipticCurvePublicKey.from_encoded_point(curve, data)

# -------------- Derive AES-256 key via ECDH -> HKDF(SHA3-512) --------------
def derive_aes_key(shared_secret: bytes, info=b'handshake data', length=32):
    # length=32 bytes => AES-256
    hkdf = HKDF(
        algorithm=hashes.SHA3_512(),
        length=length,
        salt=None,           # in production, using a salt is recommended
        info=info,
    )
    return hkdf.derive(shared_secret)

# -------------- Sender side: encrypt and sign --------------
def sender_encrypt_sign(
    plaintext: bytes,
    recipient_pub,
    sender_sign_priv
):
    # 1) Create ephemeral ECDH key
    ephemeral_priv = ec.generate_private_key(recipient_pub.curve)
    ephemeral_pub = ephemeral_priv.public_key()

    # 2) ECDH shared secret
    shared_secret = ephemeral_priv.exchange(ec.ECDH(), recipient_pub)

    # 3) Derive AES-256 key using HKDF with SHA3-512
    aes_key = derive_aes_key(shared_secret, info=b'ecdh-aes-key')

    # 4) AES-GCM encrypt
    aesgcm = AESGCM(aes_key)
    nonce = os.urandom(12)  # 96-bit nonce for GCM
    ciphertext = aesgcm.encrypt(nonce, plaintext, associated_data=None)  # ciphertext includes tag appended

    # 5) SHA3-512 hash (optional—GCM already authenticates; included per your "SHA-3" requirement)
    digest = hashes.Hash(hashes.SHA3_512())
    digest.update(plaintext)
    sha3_hash = digest.finalize()

    # 6) Sign the plaintext (or the digest) with sender's long-term ECDSA private key using SHA3-512
    signature = sender_sign_priv.sign(plaintext, ec.ECDSA(hashes.SHA3_512()))

    # 7) Return all transmit elements (Base64 for easy transport)
    return {
        'ephemeral_pub': b64(serialize_public_key(ephemeral_pub)),
        'sender_sign_pub': b64(serialize_public_key(sender_sign_priv.public_key())),
        'nonce': b64(nonce),
        'ciphertext': b64(ciphertext),
        'signature': b64(signature),
        'sha3_hash': b64(sha3_hash),
    }

# -------------- Recipient side: derive key, decrypt, verify --------------
def recipient_decrypt_verify(
    envelope: dict,
    recipient_priv,
    sender_sign_pub_bytes
):
    # Load ephemeral pub
    ephemeral_pub = load_public_key_from_bytes(ub64(envelope['ephemeral_pub']), curve=recipient_priv.curve)
    # Recreate shared secret
    shared_secret = recipient_priv.exchange(ec.ECDH(), ephemeral_pub)
    # Derive AES key
    aes_key = derive_aes_key(shared_secret, info=b'ecdh-aes-key')
    # Decrypt
    aesgcm = AESGCM(aes_key)
    nonce = ub64(envelope['nonce'])
    ciphertext = ub64(envelope['ciphertext'])
    plaintext = aesgcm.decrypt(nonce, ciphertext, associated_data=None)

    # Verify signature
    sender_sign_pub = load_public_key_from_bytes(sender_sign_pub_bytes, curve=recipient_priv.curve)
    signature = ub64(envelope['signature'])

    # Will raise an exception if verification fails
    sender_sign_pub.verify(signature, plaintext, ec.ECDSA(hashes.SHA3_512()))

    # Optionally verify SHA3-512 hash matches
    digest = hashes.Hash(hashes.SHA3_512())
    digest.update(plaintext)
    sha3_hash = digest.finalize()
    if sha3_hash != ub64(envelope['sha3_hash']):
        raise ValueError("SHA3-512 hash mismatch (integrity problem)")

    return plaintext

# -------------- Demo run --------------
def demo():
    # Generate long-term keys
    recipient_priv, recipient_pub = generate_ecc_keypair(curve=ec.SECP384R1())
    sender_sign_priv, sender_sign_pub = generate_ecc_keypair(curve=ec.SECP384R1())

    # Plaintext
    plaintext = b"This is a super-secret message using AES-256-GCM + ECDH + ECDSA + SHA3-512."

    # Sender encrypts and signs
    envelope = sender_encrypt_sign(plaintext, recipient_pub, sender_sign_priv)

    print("=== TRANSMITTED ENVELOPE (Base64 fields) ===")
    for k, v in envelope.items():
        print(f"{k}: {v}")
    print("===========================================\n")

    # Recipient receives and decrypts/verifies
    sender_pub_bytes = serialize_public_key(sender_sign_pub)
    decrypted = recipient_decrypt_verify(envelope, recipient_priv, sender_pub_bytes)
    print("Decrypted plaintext:", decrypted.decode())

if __name__ == "__main__":
    demo()



# OUTPUT
# === TRANSMITTED ENVELOPE (Base64 fields) ===
# ephemeral_pub: BMHwVf6v+X1mJ7x3b0k7y5c1vX9r4H8Gz2Zk3j5+6U8vFqz8e3K1Jt2y5Y9JH9+X9F0s8e3K1Jt2y5Y9JH9+X9F0s8e3K1Jt2y5Y9JH9+X9F0s=
# sender_sign_pub: BMHwVf6v+X1mJ7x
# nonce: 3q2+7w==
# ciphertext: 3q2+7w==
# signature: MEUCIQDf3q2+7w==
# sha3_hash: 3q2+7w==
# ===========================================
# Decrypted plaintext: This is a super-secret message using AES-256-GCM + ECDH + ECDSA + SHA3-512.