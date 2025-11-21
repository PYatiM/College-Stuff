import javax.crypto.KeyAgreement;
import java.security.*;
import java.security.spec.ECGenParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.Cipher;

public class EccKeyAgreement {
    public static void main(String[] args) throws Exception {
        // 1. Generate ECC key pairs for Alice and Bob
        KeyPairGenerator kpg = KeyPairGenerator.getInstance("EC");
        ECGenParameterSpec ecSpec = new ECGenParameterSpec("secp256r1"); // Standard NIST curve
        kpg.initialize(ecSpec, new SecureRandom());

        KeyPair aliceKeyPair = kpg.generateKeyPair();
        PublicKey alicePublicKey = aliceKeyPair.getPublic();
        PrivateKey alicePrivateKey = aliceKeyPair.getPrivate();

        KeyPair bobKeyPair = kpg.generateKeyPair();
        PublicKey bobPublicKey = bobKeyPair.getPublic();
        PrivateKey bobPrivateKey = bobKeyPair.getPrivate();

        // 2. Alice generates a shared secret with Bob's public key
        KeyAgreement aliceKeyAgree = KeyAgreement.getInstance("ECDH");
        aliceKeyAgree.init(alicePrivateKey);
        aliceKeyAgree.doPhase(bobPublicKey, true);
        byte[] aliceSharedSecret = aliceKeyAgree.generateSecret();

        // 3. Bob generates a shared secret with Alice's public key
        KeyAgreement bobKeyAgree = KeyAgreement.getInstance("ECDH");
        bobKeyAgree.init(bobPrivateKey);
        bobKeyAgree.doPhase(alicePublicKey, true);
        byte[] bobSharedSecret = bobKeyAgree.generateSecret();

        // The shared secrets derived by both parties will be identical
        System.out.println("Shared secrets match: " + MessageDigest.isEqual(aliceSharedSecret, bobSharedSecret));

        // 4. Use the shared secret to derive a symmetric key (e.g., for AES)
        // A Key Derivation Function (KDF) should ideally be used here for best practice.
        // For simplicity, we use the raw secret bytes.
        SecretKeySpec aesKey = new SecretKeySpec(aliceSharedSecret, 0, 16, "AES"); // Use first 16 bytes for AES-128

        // 5. Use the AES key to encrypt/decrypt data using javax.crypto.Cipher
        Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding"); // Example symmetric cipher
        cipher.init(Cipher.ENCRYPT_MODE, aesKey);
        byte[] encryptedMessage = cipher.doFinal("Hello, world!".getBytes("UTF-8"));

        cipher.init(Cipher.DECRYPT_MODE, aesKey);
        byte[] decryptedMessage = cipher.doFinal(encryptedMessage);

        System.out.println("Decrypted message: " + new String(decryptedMessage, "UTF-8"));
    }
}


// output

// Shared secrets match: true
// Decrypted message: Hello, world!
