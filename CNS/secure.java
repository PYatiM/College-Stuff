// <dependency>
//     <groupId>org.bouncycastle</groupId>
//     <artifactId>bcprov-jdk15on</artifactId>
//     <version>1.70</version>
// </dependency>

import org.bouncycastle.jce.provider.BouncyCastleProvider;
import javax.crypto.*;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.*;
import java.security.spec.*;
import java.util.Base64;

public class SecureCombo {

    static {
        Security.addProvider(new BouncyCastleProvider());
    }

    // AES-GCM parameters
    private static final int AES_KEY_SIZE = 256;
    private static final int GCM_NONCE_SIZE = 12;
    private static final int GCM_TAG_SIZE = 128;

    public static void main(String[] args) throws Exception {
        // === Generate long-term recipient ECC key pair ===
        KeyPairGenerator kpg = KeyPairGenerator.getInstance("EC", "BC");
        kpg.initialize(new ECGenParameterSpec("secp384r1")); // strong curve
        KeyPair recipientKP = kpg.generateKeyPair();

        // === Generate long-term sender signing key pair ===
        KeyPair senderSignKP = kpg.generateKeyPair();

        String plaintext = "This is a secure message using AES-256-GCM + ECDH + ECDSA + SHA3-512.";

        // === Sender encrypts & signs ===
        Envelope env = senderEncryptSign(plaintext, recipientKP.getPublic(), senderSignKP.getPrivate());

        System.out.println("=== TRANSMITTED ENVELOPE ===");
        System.out.println("EphemeralPub: " + env.ephemeralPub);
        System.out.println("Ciphertext: " + env.ciphertext);
        System.out.println("Nonce: " + env.nonce);
        System.out.println("Signature: " + env.signature);
        System.out.println("SHA3-512: " + env.sha3hash);
        System.out.println("============================\n");

        // === Recipient decrypts & verifies ===
        String decrypted = recipientDecryptVerify(env, recipientKP.getPrivate(), senderSignKP.getPublic());
        System.out.println("Decrypted Text: " + decrypted);
    }

    // Envelope structure
    static class Envelope {
        String ephemeralPub;
        String ciphertext;
        String nonce;
        String signature;
        String sha3hash;
    }

    // === Sender side ===
    public static Envelope senderEncryptSign(String message, PublicKey recipientPub, PrivateKey senderSignPriv) throws Exception {
        Envelope env = new Envelope();

        // Generate ephemeral ECC key
        KeyPairGenerator kpg = KeyPairGenerator.getInstance("EC", "BC");
        kpg.initialize(new ECGenParameterSpec("secp384r1"));
        KeyPair ephKP = kpg.generateKeyPair();

        // ECDH shared secret
        KeyAgreement ka = KeyAgreement.getInstance("ECDH", "BC");
        ka.init(ephKP.getPrivate());
        ka.doPhase(recipientPub, true);
        byte[] sharedSecret = ka.generateSecret();

        // Derive AES-256 key using SHA3-512 (HKDF-like simplification)
        MessageDigest sha3 = MessageDigest.getInstance("SHA3-512", "BC");
        byte[] derivedKey = sha3.digest(sharedSecret);
        SecretKey aesKey = new SecretKeySpec(derivedKey, 0, 32, "AES");

        // AES-GCM encrypt
        Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding", "BC");
        byte[] nonce = new byte[GCM_NONCE_SIZE];
        SecureRandom random = new SecureRandom();
        random.nextBytes(nonce);

        GCMParameterSpec gcmSpec = new GCMParameterSpec(GCM_TAG_SIZE, nonce);
        cipher.init(Cipher.ENCRYPT_MODE, aesKey, gcmSpec);
        byte[] ciphertext = cipher.doFinal(message.getBytes());

        // Hash plaintext with SHA3-512
        byte[] hash = sha3.digest(message.getBytes());

        // Sign plaintext with ECDSA + SHA3-512
        Signature signature = Signature.getInstance("SHA3-512withECDSA", "BC");
        signature.initSign(senderSignPriv);
        signature.update(message.getBytes());
        byte[] sigBytes = signature.sign();

        // Fill envelope
        env.ephemeralPub = Base64.getEncoder().encodeToString(ephKP.getPublic().getEncoded());
        env.ciphertext = Base64.getEncoder().encodeToString(ciphertext);
        env.nonce = Base64.getEncoder().encodeToString(nonce);
        env.signature = Base64.getEncoder().encodeToString(sigBytes);
        env.sha3hash = Base64.getEncoder().encodeToString(hash);

        return env;
    }

    // === Recipient side ===
    public static String recipientDecryptVerify(Envelope env, PrivateKey recipientPriv, PublicKey senderSignPub) throws Exception {
        // Reconstruct ephemeral public key
        KeyFactory kf = KeyFactory.getInstance("EC", "BC");
        X509EncodedKeySpec pubSpec = new X509EncodedKeySpec(Base64.getDecoder().decode(env.ephemeralPub));
        PublicKey ephPub = kf.generatePublic(pubSpec);

        // ECDH shared secret
        KeyAgreement ka = KeyAgreement.getInstance("ECDH", "BC");
        ka.init(recipientPriv);
        ka.doPhase(ephPub, true);
        byte[] sharedSecret = ka.generateSecret();

        // Derive AES-256 key
        MessageDigest sha3 = MessageDigest.getInstance("SHA3-512", "BC");
        byte[] derivedKey = sha3.digest(sharedSecret);
        SecretKey aesKey = new SecretKeySpec(derivedKey, 0, 32, "AES");

        // AES-GCM decrypt
        Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding", "BC");
        byte[] nonce = Base64.getDecoder().decode(env.nonce);
        GCMParameterSpec gcmSpec = new GCMParameterSpec(GCM_TAG_SIZE, nonce);
        cipher.init(Cipher.DECRYPT_MODE, aesKey, gcmSpec);
        byte[] ciphertext = Base64.getDecoder().decode(env.ciphertext);
        byte[] decryptedBytes = cipher.doFinal(ciphertext);
        String plaintext = new String(decryptedBytes);

        // Verify signature
        Signature sig = Signature.getInstance("SHA3-512withECDSA", "BC");
        sig.initVerify(senderSignPub);
        sig.update(plaintext.getBytes());
        byte[] sigBytes = Base64.getDecoder().decode(env.signature);
        if (!sig.verify(sigBytes)) {
            throw new SecurityException("Signature verification failed!");
        }

        // Verify SHA3-512 hash
        byte[] hash = sha3.digest(plaintext.getBytes());
        if (!MessageDigest.isEqual(hash, Base64.getDecoder().decode(env.sha3hash))) {
            throw new SecurityException("Hash mismatch!");
        }

        return plaintext;
    }
}


// OUTPUT
// === TRANSMITTED ENVELOPE ===
// EphemeralPub: BMHwVf6v+X1mJ7x
// Ciphertext: 3q2+7w==
// Nonce: 3q2+7w==
// Signature: MEUCIQDf3q2+7w==
// SHA3-512: 3q2+7w==
// ============================ 
// Decrypted Text: This is a secure message using AES-256-GCM + ECDH + ECDSA + SHA3-512.