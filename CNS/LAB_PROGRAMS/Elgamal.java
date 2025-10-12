import java.math.BigInteger;
import java.util.Scanner;
import java.security.SecureRandom;

public class ElGamalShort {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // 1. Setup: Define a large prime p and a generator g
        BigInteger p = new BigInteger("23"); // Small prime for demonstration
        BigInteger g = new BigInteger("5");  // A generator for p=23

        System.out.println("Using public parameters p=" + p + " and g=" + g);

        // 2. Key Generation
        System.out.print("Enter your private key (an integer x < p): ");
        BigInteger x = sc.nextBigInteger(); // Alice's private key

        // Calculate public key: y = g^x mod p
        BigInteger y = g.modPow(x, p);
        System.out.println("Your public key is y=" + y);

        // 3. Encryption
        System.out.print("\nEnter the message to encrypt (an integer M < p): ");
        BigInteger M = sc.nextBigInteger();

        // Generate a random ephemeral key k
        BigInteger k = new BigInteger(p.bitLength() - 1, new SecureRandom());
        System.out.println("Using a random ephemeral key k=" + k);
        
        // Ciphertext (c1, c2)
        // c1 = g^k mod p
        BigInteger c1 = g.modPow(k, p);
        // c2 = M * y^k mod p
        BigInteger c2 = M.multiply(y.modPow(k, p)).mod(p);

        System.out.println("Encrypted ciphertext (c1, c2) = (" + c1 + ", " + c2 + ")");

        // 4. Decryption
        // s = c1^x mod p
        BigInteger s = c1.modPow(x, p);
        // M = c2 * s^-1 mod p
        BigInteger decryptedMessage = c2.multiply(s.modInverse(p)).mod(p);
        
        System.out.println("\nDecrypted Message: " + decryptedMessage);
        
        sc.close();
    }
}
