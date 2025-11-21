import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.util.Base64;

public class AESCipher {

    private static final String ALGORITHM = "AES/CBC/PKCS5Padding";
    private static final String KEY_STRING = "UJJWALA123456789"; // Must be 16, 24, or 32 bytes
    private static final String IV_STRING = "ThisIsAnIVString"; // Must be 16 bytes

    public static String encrypt(String plainText) throws Exception {
        SecretKeySpec secretKey = new SecretKeySpec(KEY_STRING.getBytes(StandardCharsets.UTF_8), "AES");
        IvParameterSpec ivSpec = new IvParameterSpec(IV_STRING.getBytes(StandardCharsets.UTF_8));

        Cipher cipher = Cipher.getInstance(ALGORITHM);
        cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivSpec);

        byte[] encryptedBytes = cipher.doFinal(plainText.getBytes(StandardCharsets.UTF_8));
        return Base64.getEncoder().encodeToString(encryptedBytes);
    }

    public static String decrypt(String encryptedText) throws Exception {
        SecretKeySpec secretKey = new SecretKeySpec(KEY_STRING.getBytes(StandardCharsets.UTF_8), "AES");
        IvParameterSpec ivSpec = new IvParameterSpec(IV_STRING.getBytes(StandardCharsets.UTF_8));

        Cipher cipher = Cipher.getInstance(ALGORITHM);
        cipher.init(Cipher.DECRYPT_MODE, secretKey, ivSpec);

        byte[] originalBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedText));
        return new String(originalBytes, StandardCharsets.UTF_8);
    }

    public static void main(String[] args) {
        try {
            String originalString = "Welcome to DSU!";
            System.out.println("Original String: " + originalString);

            String encryptedString = encrypt(originalString);
            System.out.println("Encrypted String: " + encryptedString);

            String decryptedString = decrypt(encryptedString);
            System.out.println("Decrypted String: " + decryptedString);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}