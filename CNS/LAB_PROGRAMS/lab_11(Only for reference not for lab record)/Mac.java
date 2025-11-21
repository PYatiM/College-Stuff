Message authentication code:

    import javax.crypto.Mac;
    import javax.crypto.spec.SecretKeySpec;
    import java.security.InvalidKeyException;
    import java.security.NoSuchAlgorithmException;

    public class MacExample {
        public static void main(String[] args) {
            try {
                // Secret key for MAC calculation
                byte[] keyBytes = "mysecretkey".getBytes();
                SecretKeySpec secretKey = new SecretKeySpec(keyBytes, "HmacSHA256");

                // Get a Mac instance for HmacSHA256
                Mac mac = Mac.getInstance("HmacSHA256");

                // Initialize the Mac with the secret key
                mac.init(secretKey);

                // Message to be authenticated
                byte[] message = "This is a test message.".getBytes();

                // Calculate the MAC
                byte[] macResult = mac.doFinal(message);

                System.out.println("MAC: " + bytesToHex(macResult));

            } catch (NoSuchAlgorithmException | InvalidKeyException e) {
                e.printStackTrace();
            }
        }

        // Helper method to convert byte array to hex string
        private static String bytesToHex(byte[] bytes) {
            StringBuilder sb = new StringBuilder();
            for (byte b : bytes) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        }
    }