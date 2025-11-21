SHA-2 Implementation code is given below:
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.nio.charset.StandardCharsets;
import java.math.BigInteger;

public class Sha256HashGenerator {

    public static String generateSha256(String input) throws NoSuchAlgorithmException {
        // Get an instance of the SHA-256 MessageDigest
        MessageDigest md = MessageDigest.getInstance("SHA-256");

        // Convert the input string to bytes using UTF-8 encoding
        byte[] hash = md.digest(input.getBytes(StandardCharsets.UTF_8));

        // Convert the byte array to a hexadecimal string representation
        BigInteger number = new BigInteger(1, hash);
        StringBuilder hexString = new StringBuilder(number.toString(16));

        // Pad with leading zeros to ensure a 64-character hexadecimal string
        while (hexString.length() < 64) {
            hexString.insert(0, '0');
        }

        return hexString.toString();
    }

    public static void main(String[] args) {
        try {
            String data = "This is a test string for SHA-256 hashing.";
            String sha256Hash = generateSha256(data);

            System.out.println("Original String: " + data);
            System.out.println("SHA-256 Hash: " + sha256Hash);

            String anotherData = "Hello, World!";
            String anotherSha256Hash = generateSha256(anotherData);
            System.out.println("\nOriginal String: " + anotherData);
            System.out.println("SHA-256 Hash: " + anotherSha256Hash);

        } catch (NoSuchAlgorithmException e) {
            System.err.println("SHA-256 algorithm not found: " + e.getMessage());
        }
    }
}