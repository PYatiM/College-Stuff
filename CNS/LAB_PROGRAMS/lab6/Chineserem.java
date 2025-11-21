import java.math.BigInteger;
import java.util.Scanner;

public class ChineseRemainderTheorem {

    /**
     * Solves a system of congruences x ≡ a[i] (mod m[i]) using the Chinese Remainder Theorem.
     * All moduli in m[] are assumed to be pairwise coprime.
     * @param a The array of remainders.
     * @param m The array of moduli.
     * @return The solution x.
     */
    public static BigInteger solveCRT(BigInteger[] a, BigInteger[] m) {
        // 1. Calculate M = product of all moduli
        BigInteger M = BigInteger.ONE;
        for (BigInteger mi : m) {
            M = M.multiply(mi);
        }

        BigInteger solution = BigInteger.ZERO;
        for (int i = 0; i < a.length; i++) {
            // 2. For each equation, find Mi and its inverse
            BigInteger Mi = M.divide(m[i]);
            BigInteger Mi_inv = Mi.modInverse(m[i]);

            // 3. Add the term a[i] * Mi * Mi_inv to the solution
            BigInteger term = a[i].multiply(Mi).multiply(Mi_inv);
            solution = solution.add(term);
        }

        // 4. The final result is the solution modulo M
        return solution.mod(M);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of equations: ");
        int n = sc.nextInt();

        BigInteger[] a = new BigInteger[n]; // Remainders
        BigInteger[] m = new BigInteger[n]; // Moduli

        System.out.println("Enter the remainders (a_i) and moduli (m_i):");
        for (int i = 0; i < n; i++) {
            System.out.print("For equation " + (i + 1) + ", a_" + (i+1) + ": ");
            a[i] = sc.nextBigInteger();
            System.out.print("For equation " + (i + 1) + ", m_" + (i+1) + ": ");
            m[i] = sc.nextBigInteger();
        }

        // The core logic is now just one line
        BigInteger solution = solveCRT(a, m);
        
        // Calculate M for the final output
        BigInteger M = BigInteger.ONE;
        for (BigInteger mi : m) {
            M = M.multiply(mi);
        }

        System.out.println("\nThe solution is x ≡ " + solution + " (mod " + M + ")");
        sc.close();
    }
}

