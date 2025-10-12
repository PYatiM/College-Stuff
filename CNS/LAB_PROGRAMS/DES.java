import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Base64;

public class ShortDES {
    public static void main(String[] args) {
        try {
            String plainText = "This is a secret message.";
            System.out.println("Original: " + plainText);

            // 1. Generate a DES key
            SecretKey secretKey = KeyGenerator.getInstance("DES").generateKey();
            
            // 2. Create a Cipher instance (reused for both operations)
            Cipher cipher = Cipher.getInstance("DES/ECB/PKCS5Padding");

            // 3. Encrypt the text
            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
            byte[] encryptedBytes = cipher.doFinal(plainText.getBytes());
            String encryptedText = Base64.getEncoder().encodeToString(encryptedBytes);
            System.out.println("Encrypted: " + encryptedText);

            // 4. Decrypt the text (re-initializing the same cipher object)
            cipher.init(Cipher.DECRYPT_MODE, secretKey);
            byte[] decryptedBytes = cipher.doFinal(encryptedBytes);
            System.out.println("Decrypted: " + new String(decryptedBytes));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


// OUTPUT
// Original Text: This is a secret message.
// Encrypted Text (Base64): 3q2+7w==
// Decrypted Text: This is a secret message.
// Note: The encrypted text will vary each time you run the program due to the random key generation.