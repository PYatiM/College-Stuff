import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5HashGenerator {

    public static String generateMD5(String input) {
        try {
            // Get an MD5 MessageDigest instance
            MessageDigest md = MessageDigest.getInstance("MD5");

            // Compute the message digest of the input bytes
            byte[] messageDigest = md.digest(input.getBytes());

            // Convert the byte array into a signum representation BigInteger
            BigInteger no = new BigInteger(1, messageDigest);

            // Convert the BigInteger into a hexadecimal string
            String hashtext = no.toString(16);

            // Pad the hash string with leading zeros if necessary to ensure 32 characters
            while (hashtext.length() < 32) {
                hashtext = "0" + hashtext;
            }
            return hashtext;
        } catch (NoSuchAlgorithmException e) {
            // Handle the case where the MD5 algorithm is not available
            throw new RuntimeException("MD5 algorithm not found", e);
        }
    }

    public static void main(String[] args) {
        String data = "This is a test string for MD5 hashing.";
        String md5Hash = generateMD5(data);
        System.out.println("MD5 Hash of \"" + data + "\": " + md5Hash);
    }
}