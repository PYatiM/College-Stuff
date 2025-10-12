import java.util.Scanner;

public class ElGamal {
    public static long[] extendedGCD(long a, long b) {
        if (b == 0) {
            return new long[]{a, 1, 0};
        } else {
            long[] vals = extendedGCD(b, a % b);
            long gcd = vals[0];
            long x1 = vals[1];
            long y1 = vals[2];
            long x = y1;
            long y = x1 - (a / b) * y1;
            return new long[]{gcd, x, y};
        }
    }

    public static long modInverse(long a, long m) {
        long[] vals = extendedGCD(a, m);
        long gcd = vals[0];
        long x = vals[1];
        if (gcd != 1) {
            throw new ArithmeticException("Modular inverse does not exist");
        }
        return (x % m + m) % m;
    }
    
    public static long modPow(long base, long exp, long mod) {
        long result = 1;
        base = base % mod;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            exp >>= 1;
            base = (base * base) % mod;
        }
        return result;
    }

    public static long[] encrypt(long p, long g, long y, long message, long k) {
        long c1 = modPow(g, k, p);
        long c2 = (message * modPow(y, k, p)) % p;

        System.out.println("\n--- Encryption Steps ---");
        System.out.println("Using ephemeral key k = " + k);
        System.out.println("Step 1: c1 = g^k mod p = " + g + "^" + k + " mod " + p + " = " + c1);
        System.out.println("Step 2: c2 = M * y^k mod p = " + message + " * " + y + "^" + k + " mod " + p + " = " + c2);

        return new long[]{c1, c2};
    }

    public static long decrypt(long p, long x, long c1, long c2) {
        long s = modPow(c1, x, p);
        long s_inv = modInverse(s, p);
        long message = (c2 * s_inv) % p;

        System.out.println("\n--- Decryption Steps ---");
        System.out.println("Step 1: Shared secret s = c1^x mod p = " + c1 + "^" + x + " mod " + p + " = " + s);
        System.out.println("Step 2: Modular inverse of s: s^-1 mod p = " + s_inv);
        System.out.println("Step 3: Recovered message: M = c2 * s^-1 mod p = " + c2 + " * " + s_inv + " mod " + p + " = " + message);

        return message;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("=== ElGamal Encryption & Decryption ===");
        System.out.println("1. Encryption");
        System.out.println("2. Decryption");
        System.out.print("Choose an option (1 or 2): ");
        int choice = sc.nextInt();

        if (choice == 1) {
            System.out.println("\n--- Encryption ---");
            System.out.print("Enter prime number p: ");
            long p = sc.nextLong();
            System.out.print("Enter generator g: ");
            long g = sc.nextLong();
            System.out.print("Enter private key x (secret): ");
            long x = sc.nextLong();
            long y = modPow(g, x, p);
            System.out.println("Public key y = g^x mod p = " + y);

            System.out.print("Enter message M (integer < p): ");
            long message = sc.nextLong();

            System.out.println("Note: k must be in the range [2, " + (p - 2) + "]");
            System.out.print("Enter ephemeral key k: ");
            long k = sc.nextLong();
            if (k < 2 || k > p - 2) {
                throw new IllegalArgumentException("k must be between 2 and " + (p - 2));
            }

            long[] ciphertext = encrypt(p, g, y, message, k);
            System.out.println("\nCiphertext: (c1, c2) = (" + ciphertext[0] + ", " + ciphertext[1] + ")");

        } else if (choice == 2) {
            System.out.println("\n--- Decryption ---");
            System.out.print("Enter prime number p: ");
            long p = sc.nextLong();
            System.out.print("Enter private key x: ");
            long x = sc.nextLong();
            System.out.print("Enter ciphertext c1: ");
            long c1 = sc.nextLong();
            System.out.print("Enter ciphertext c2: ");
            long c2 = sc.nextLong();

            long message = decrypt(p, x, c1, c2);
            System.out.println("\nDecrypted message: " + message);

        } else {
            System.out.println("Invalid choice. Please select 1 or 2.");
        }

        sc.close();
    }
}
