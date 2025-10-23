import java.math.BigInteger;
import java.util.Scanner;

public class RSA {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // 1. Key Generation
        System.out.print("Enter two distinct prime numbers (p and q): ");
        BigInteger p = sc.nextBigInteger();
        BigInteger q = sc.nextBigInteger();

        // Calculate n = p * q
        BigInteger n = p.multiply(q);
        // Calculate phi(n) = (p-1) * (q-1)
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));

        // Find e such that 1 < e < phi(n) and gcd(e, phi) = 1
        BigInteger e = new BigInteger("3");
        while (!phi.gcd(e).equals(BigInteger.ONE)) {
            e = e.add(new BigInteger("2"));
        }

        // Calculate d, the modular multiplicative inverse of e (mod phi)
        BigInteger d = e.modInverse(phi);

        System.out.println("\nPublic key: (n=" + n + ", e=" + e + ")");
        System.out.println("Private key: (n=" + n + ", d=" + d + ")");

        // 2. Encryption
        System.out.print("\nEnter the message to encrypt (as a number): ");
        BigInteger message = sc.nextBigInteger();

        // Check if message is smaller than n
        if (message.compareTo(n) >= 0) {
            System.out.println("Error: Message must be less than n.");
        } else {
            // Encrypt: ciphertext = message^e mod n
            BigInteger ciphertext = message.modPow(e, n);
            System.out.println("Encrypted message: " + ciphertext);

            // Decrypt: decrypted_message = ciphertext^d mod n
            BigInteger decryptedMessage = ciphertext.modPow(d, n);
            System.out.println("Decrypted message: " + decryptedMessage);
        }

        sc.close();
    }
}