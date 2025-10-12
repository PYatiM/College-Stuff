import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;
import java.nio.ByteBuffer;
import java.security.SecureRandom;
import java.util.Base64;

public class ShortAES {

    // AES is a block cipher, and GCM is a recommended mode of operation.
    // GCM is an authenticated encryption mode, which provides confidentiality and authenticity.
    private static final String ALGORITHM = "AES/GCM/NoPadding";
    private static final int KEY_SIZE = 256; // Can be 128, 192, or 256
    private static final int GCM_IV_LENGTH = 12; // 96 bits is recommended for GCM
    private static final int GCM_TAG_LENGTH = 128; // Authentication tag length in bits

    public static void main(String[] args) {
        try {
            String plainText = "This is a modern secret message.";
            System.out.println("Original: " + plainText);

            // 1. Generate a strong AES key
            KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
            keyGenerator.init(KEY_SIZE);
            SecretKey secretKey = keyGenerator.generateKey();

            // --- Encryption ---
            Cipher cipher = Cipher.getInstance(ALGORITHM);

            // Generate a random Initialization Vector (IV)
            byte[] iv = new byte[GCM_IV_LENGTH];
            new SecureRandom().nextBytes(iv);
            
            GCMParameterSpec gcmParameterSpec = new GCMParameterSpec(GCM_TAG_LENGTH, iv);
            cipher.init(Cipher.ENCRYPT_MODE, secretKey, gcmParameterSpec);
            
            byte[] encryptedBytes = cipher.doFinal(plainText.getBytes());

            // Prepend the IV to the ciphertext for use during decryption
            ByteBuffer byteBuffer = ByteBuffer.allocate(iv.length + encryptedBytes.length);
            byteBuffer.put(iv);
            byteBuffer.put(encryptedBytes);
            byte[] cipherMessage = byteBuffer.array();

            String encryptedText = Base64.getEncoder().encodeToString(cipherMessage);
            System.out.println("Encrypted: " + encryptedText);

            // --- Decryption ---
            // Extract the IV from the beginning of the cipher message
            ByteBuffer decryptBuffer = ByteBuffer.wrap(Base64.getDecoder().decode(encryptedText));
            byte[] ivToDecrypt = new byte[GCM_IV_LENGTH];
            decryptBuffer.get(ivToDecrypt);
            byte[] encryptedBytesToDecrypt = new byte[decryptBuffer.remaining()];
            decryptBuffer.get(encryptedBytesToDecrypt);

            // Re-initialize the cipher for decryption
            GCMParameterSpec decryptSpec = new GCMParameterSpec(GCM_TAG_LENGTH, ivToDecrypt);
            cipher.init(Cipher.DECRYPT_MODE, secretKey, decryptSpec);

            byte[] decryptedBytes = cipher.doFinal(encryptedBytesToDecrypt);
            System.out.println("Decrypted: " + new String(decryptedBytes));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
