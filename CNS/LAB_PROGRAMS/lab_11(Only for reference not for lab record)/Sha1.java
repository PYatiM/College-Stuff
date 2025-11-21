import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class SHA1Example {

    public static void main(String[] args) {
        String message = "This is a test message for SHA-1 hashing.";
        try {
            // Get an instance of the SHA-1 MessageDigest algorithm
            MessageDigest md = MessageDigest.getInstance("SHA-1");

            // Update the message digest with the input message bytes
            md.update(message.getBytes());

            // Compute the SHA-1 hash (message digest)
            byte[] sha1Hash = md.digest();

            // Convert the byte array to a hexadecimal string for display
            StringBuilder hexString = new StringBuilder();
            for (byte b : sha1Hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) {
                    hexString.append('0');
                }
                hexString.append(hex);
            }
            System.out.println("SHA-1 Hash: " + hexString.toString());

        } catch (NoSuchAlgorithmException e) {
            System.err.println("SHA-1 algorithm not found: " + e.getMessage());
        }
    }
}