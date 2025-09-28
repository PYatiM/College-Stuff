import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;

public class Main {

    public static void main(String[] args) throws Exception {
        // 1. Generate a DES Key
        KeyGenerator keygenerator = KeyGenerator.getInstance("DES");
        SecretKey secretKey = keygenerator.generateKey();

        // 2. Data to be encrypted
        String plaintext = "This is a secret message.";
        System.out.println("Original Text: " + plaintext);

        // 3. Encrypt the data
        byte[] encryptedBytes = encrypt(plaintext.getBytes(), secretKey);
        String encryptedText = Base64.getEncoder().encodeToString(encryptedBytes);
        System.out.println("Encrypted Text (Base64): " + encryptedText);

        // 4. Decrypt the data
        byte[] decryptedBytes = decrypt(encryptedBytes, secretKey);
        String decryptedText = new String(decryptedBytes);
        System.out.println("Decrypted Text: " + decryptedText);
    }

    public static byte[] encrypt(byte[] plaintext, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding"); // DES algorithm, Electronic Codebook mode, PKCS5 padding
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        return cipher.doFinal(plaintext);
    }

    public static byte[] decrypt(byte[] ciphertext, SecretKey secretKey) throws Exception {
        Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        return cipher.doFinal(ciphertext);
    }
}


// OUTPUT
// Original Text: This is a secret message.
// Encrypted Text (Base64): 3q2+7w==
// Decrypted Text: This is a secret message.
// Note: The encrypted text will vary each time you run the program due to the random key generation.