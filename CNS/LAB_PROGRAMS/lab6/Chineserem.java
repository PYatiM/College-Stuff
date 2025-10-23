// The Chinese Remainder Theorem (CRT) is used to solve a system of simultaneous congruences. It finds a solution that satisfies all the given modular equations. The moduli must be pairwise coprime (i.e., gcd of each pair is 1).

// ### Steps to Solve using CRT:

// 1. **Write down the system of congruences:**
//    - x ≡ a₁ (mod m₁)
//    - x ≡ a₂ (mod m₂)
//    - x ≡ a₃ (mod m₃)
   
// 2. **Find the product of all moduli:**
//    - M = m₁ * m₂ * m₃

// 3. **For each congruence, calculate the partial products:**
//    - M₁ = M / m₁
//    - M₂ = M / m₂
//    - M₃ = M / m₃

// 4. **Find the multiplicative inverse of each partial product modulo the corresponding modulus:**
//    - Find M₁⁻¹ (mod m₁)
//    - Find M₂⁻¹ (mod m₂)
//    - Find M₃⁻¹ (mod m₃)

// 5. **Construct the solution:**
//    x = (a₁ * M₁ * M₁⁻¹) + (a₂ * M₂ * M₂⁻¹) + (a₃ * M₃ * M₃⁻¹)

// 6. **Take the result modulo M (the product of all moduli):**
//    x ≡ result (mod M)

// ---

// ### Example:

// Given the system:
// - x ≡ 2 (mod 3)
// - x ≡ 3 (mod 5)
// - x ≡ 1 (mod 7)

// #### Step 1: Find the product of all moduli.
// M = 3 * 5 * 7 = 105

// #### Step 2: Find the partial products:
// M₁ = 105 / 3 = 35
// M₂ = 105 / 5 = 21
// M₃ = 105 / 7 = 15

// #### Step 3: Find the multiplicative inverses:
// - Find M₁⁻¹ (mod 3): M₁⁻¹ = 2 (since 35 ≡ 2 mod 3)
// - Find M₂⁻¹ (mod 5): M₂⁻¹ = 1 (since 21 ≡ 1 mod 5)
// - Find M₃⁻¹ (mod 7): M₃⁻¹ = 1 (since 15 ≡ 1 mod 7)

// #### Step 4: Construct the solution:
// x = (2 * 35 * 2) + (3 * 21 * 1) + (1 * 15 * 1)
// x = 140 + 63 + 15 = 218

// #### Step 5: Take x mod 105:
// x = 218 mod 105
// x = 218 - 2 * 105 = 218 - 210 = 8

// ---

// ### Final Answer:
// x = 8

// This satisfies all the congruences:
// - 8 ≡ 2 (mod 3)
// - 8 ≡ 3 (mod 5)
// - 8 ≡ 1 (mod 7)
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



// The Chinese Remainder Theorem (CRT) is used to solve a system of simultaneous congruences.
// It finds a solution that satisfies all the given modular equations.
// The moduli must be pairwise coprime (i.e., gcd of each pair is 1).
