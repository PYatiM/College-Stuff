// RSA Algorithm

#include <stdio.h>
#include <stdlib.h>

long long power(long long base, long long pow, long long mod){
	long long res = 1;
	base = base % mod;
	while(pow>0){
		if(pow & 1)
			res = (res * base) % mod;
		base = (base * base) % mod;
		pow = pow/2;
	}
	return res;
}

long long modulo(long long a, long long b){
	long long q, r, t1=1, t0=0, tn, oa = a;
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

long long key(long long p, long long q, long long e){
	long long phin = (p-1)*(q-1);
	long long d = modulo(phin,e);
	return d;	
}

long long encrypt(long long m, long long e, long long n){
	return power(m,e,n);
}

long long decrypt(long long c, long long d, long long n){
	return power(c,d,n);
}

long long find_coprime(long long phin) {
    long long e = 3;
    while (e < phin) {
        long a = phin, b = e, temp;
        while(b != 0){
            temp = a % b;
            a = b;
            b = temp;
        }
        if(a == 1)
            return e;
        e += 2; 
    }
    return -1; 
}

int main(){
	long long n, m, p, q;
	
	printf("Enter two co primes : ");
	scanf("%lld %lld",&p,&q);
	
	n = p * q;
	
	long long phin = (p - 1) * (q - 1);
	
	long long e = find_coprime(phin);
	if (e == -1) {
    		printf("Failed to find a valid e\n");
    		return 1;
	}

	long a = phin,b = e, temp;
	while(b!=0){
		temp = a % b;
		a = b;
		b = temp;
	}
	if(a != 1){
		printf("e and phin are not coprime. Choose different primes or e.\n");
		return 1;
	}
	
	long long d = key(p, q, e); 
	
	printf("Public key : (%lld,%lld)\n", n, e);
	printf("Private key : (%lld,%lld)\n", n, d);
	
	printf("Enter the number to encrypt : ");
	scanf("%lld", &m);

	if (m >= n) {
    	printf("Error: The message (%lld) must be less than modulus n (%lld)\n", m, n);
    	return 1;
	}

	long long encrypt_c = encrypt(m, e, n);
	printf("Encrypted message : %lld\n", encrypt_c);

	long long decrypt_m = decrypt(encrypt_c, d, n);
	printf("Decrypted message : %lld\n", decrypt_m);

	return 0;
}

//output
// Enter two co primes : 67 53
// Public key : (3551,5)
// Private key : (3551,1373)
// Enter the number to encrypt : 123
// Encrypted message : 888
// Decrypted message : 123

