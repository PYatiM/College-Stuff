import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.SecureRandom;
import java.util.Base64;

public class TripleDESExample {

    public static void main(String[] args) throws Exception {
        String plaintext = "This is a secret message.";

        // 1. Generate a 3DES Key
        KeyGenerator keyGen = KeyGenerator.getInstance("DESede");
        keyGen.init(192); // 192-bit key
        SecretKey secretKey = keyGen.generateKey();
        byte[] keyBytes = secretKey.getEncoded();
        SecretKeySpec keySpec = new SecretKeySpec(keyBytes, "DESede");

        // 2. Generate a random IV
        SecureRandom random = new SecureRandom();
        byte[] ivBytes = new byte[8]; // 8-byte IV for DESede
        random.nextBytes(ivBytes);
        IvParameterSpec ivSpec = new IvParameterSpec(ivBytes);

        // 3. Initialize and Encrypt
        Cipher cipher = Cipher.getInstance("DESede/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, keySpec, ivSpec);
        byte[] encryptedBytes = cipher.doFinal(plaintext.getBytes("UTF-8"));
        String encodedCiphertext = Base64.getEncoder().encodeToString(encryptedBytes);
        System.out.println("Encrypted: " + encodedCiphertext);

        // 4. Initialize and Decrypt
        Cipher decipher = Cipher.getInstance("DESede/CBC/PKCS5Padding");
        decipher.init(Cipher.DECRYPT_MODE, keySpec, ivSpec);
        byte[] decodedEncryptedBytes = Base64.getDecoder().decode(encodedCiphertext);
        byte[] decryptedBytes = decipher.doFinal(decodedEncryptedBytes);
        String decryptedText = new String(decryptedBytes, "UTF-8");
        System.out.println("Decrypted: " + decryptedText);
    }
}

// output
// Encrypted: QgZq0P4lEoZ3aN3sJd6t2fT8qN6m4B3YpVvTqgX8Y2E=
// Decrypted: This is a secret message.
