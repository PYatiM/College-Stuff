import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.security.SecureRandom;
import java.util.Base64;

public class DoubleDES {

    public static SecretKey generateDESKey() throws Exception {
        KeyGenerator keyGenerator = KeyGenerator.getInstance("DES");
        keyGenerator.init(new SecureRandom()); // Use a secure random source
        return keyGenerator.generateKey();
    }

    public static byte[] encrypt(byte[] plaintext, SecretKey key1, SecretKey key2) throws Exception {
        // First DES encryption
        Cipher cipher1 = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher1.init(Cipher.ENCRYPT_MODE, key1);
        byte[] intermediateCiphertext = cipher1.doFinal(plaintext);

        // Second DES encryption
        Cipher cipher2 = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher2.init(Cipher.ENCRYPT_MODE, key2);
        byte[] finalCiphertext = cipher2.doFinal(intermediateCiphertext);

        return finalCiphertext;
    }

    public static byte[] decrypt(byte[] ciphertext, SecretKey key1, SecretKey key2) throws Exception {
        // First DES decryption (with key2)
        Cipher cipher2 = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher2.init(Cipher.DECRYPT_MODE, key2);
        byte[] intermediatePlaintext = cipher2.doFinal(ciphertext);

        // Second DES decryption (with key1)
        Cipher cipher1 = Cipher.getInstance("DES/ECB/PKCS5Padding");
        cipher1.init(Cipher.DECRYPT_MODE, key1);
        byte[] finalPlaintext = cipher1.doFinal(intermediatePlaintext);

        return finalPlaintext;
    }

    public static void main(String[] args) throws Exception {
        // Generate two distinct DES keys
        SecretKey key1 = generateDESKey();
        SecretKey key2 = generateDESKey();

        String originalText = "This is a secret message for Double DES.";
        byte[] plaintextBytes = originalText.getBytes("UTF-8");

        // Encrypt
        byte[] encryptedBytes = encrypt(plaintextBytes, key1, key2);
        String encryptedText = Base64.getEncoder().encodeToString(encryptedBytes);
        System.out.println("Encrypted Text: " + encryptedText);

        // Decrypt
        byte[] decryptedBytes = decrypt(encryptedBytes, key1, key2);
        String decryptedText = new String(decryptedBytes, "UTF-8");
        System.out.println("Decrypted Text: " + decryptedText);
    }
}