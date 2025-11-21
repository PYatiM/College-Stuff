import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import javax.crypto.spec.IvParameterSpec;
import java.security.SecureRandom;
import java.util.Base64;

public class Blowfish {

    private static final String ALGORITHM = "Blowfish";
    private static final String TRANSFORMATION = "Blowfish/CBC/PKCS5Padding"; // Or "Blowfish/ECB/PKCS5Padding"

    public static SecretKey generateKey() throws Exception {
        KeyGenerator keyGen = KeyGenerator.getInstance(ALGORITHM);
        keyGen.init(128); // Key size can be 32 to 448 bits, commonly 128 or 256
        return keyGen.generateKey();
    }

    public static byte[] encrypt(String plaintext, SecretKey secretKey, byte[] iv) throws Exception {
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        IvParameterSpec ivSpec = new IvParameterSpec(iv);
        cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivSpec);
        return cipher.doFinal(plaintext.getBytes());
    }

    public static String decrypt(byte[] ciphertext, SecretKey secretKey, byte[] iv) throws Exception {
        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        IvParameterSpec ivSpec = new IvParameterSpec(iv);
        cipher.init(Cipher.DECRYPT_MODE, secretKey, ivSpec);
        byte[] decryptedBytes = cipher.doFinal(ciphertext);
        return new String(decryptedBytes);
    }

    public static void main(String[] args) {
        try {
            // 1. Generate a Blowfish key
            SecretKey secretKey = generateKey();
            System.out.println("Generated Key: " + Base64.getEncoder().encodeToString(secretKey.getEncoded()));

            // 2. Generate an Initialization Vector (IV) for CBC mode
            SecureRandom random = new SecureRandom();
            byte[] iv = new byte[8]; // Blowfish block size is 8 bytes (64 bits)
            random.nextBytes(iv);
            System.out.println("Generated IV: " + Base64.getEncoder().encodeToString(iv));

            // 3. Define the plaintext
            String plaintext = "This is a secret message!";
            System.out.println("Original Plaintext: " + plaintext);

            // 4. Encrypt the plaintext
            byte[] encryptedBytes = encrypt(plaintext, secretKey, iv);
            String encryptedText = Base64.getEncoder().encodeToString(encryptedBytes);
            System.out.println("Encrypted Text (Base64): " + encryptedText);

            // 5. Decrypt the ciphertext
            String decryptedText = decrypt(encryptedBytes, secretKey, iv);
            System.out.println("Decrypted Text: " + decryptedText);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}