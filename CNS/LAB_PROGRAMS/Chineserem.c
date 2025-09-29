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

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modulo(int a, int b){
	int q, r, t1=1, t0=0, tn, oa = a;
	while(b!=0){
		q = a / b;
		r = a % b;
		a = b;
		b = r;
		tn = t0 - (q*t1);
		t0 = t1;
		t1 = tn;
	}
	if(t0 < 0) t0 += oa;
	return t0;
}
int chineseRemainderTheorem(int a[], int m[], int n) {
    int M = 1; // Product of all moduli
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }

    int x = 0; // Result
    for (int i = 0; i < n; i++) {
        int Mi = M / m[i];
        int Mi_inv = modInverse(Mi, m[i]);
        x += a[i] * Mi * Mi_inv;
    }

    return x % M;
}
int main() {
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));
    int *m = (int *)malloc(n * sizeof(int));

    printf("Enter the remainders (a_i) and moduli (m_i):\n");
    for (int i = 0; i < n; i++) {
        printf("Equation %d: x ≡ ", i + 1);
        scanf("%d", &a[i]);
        printf("          mod ");
        scanf("%d", &m[i]);
    }

    // Check if moduli are pairwise coprime
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (gcd(m[i], m[j]) != 1) {
                printf("Moduli are not pairwise coprime. Exiting.\n");
                free(a);
                free(m);
                return 1;
            }
        }
    }

    int result = chineseRemainderTheorem(a, m, n);
    printf("The solution is x ≡ %d (mod %d)\n", result, m[0] * m[1] * m[2]); // Assuming n=3 for simplicity

    free(a);
    free(m);
    return 0;
}
// The Chinese Remainder Theorem (CRT) is used to solve a system of simultaneous congruences.
// It finds a solution that satisfies all the given modular equations.
// The moduli must be pairwise coprime (i.e., gcd of each pair is 1).
