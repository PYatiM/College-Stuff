import java.math.BigInteger;
import java.util.Random;

public class MillerRabin {

    private static final BigInteger ONE = BigInteger.ONE;
    private static final BigInteger TWO = BigInteger.valueOf(2);
    private static final BigInteger THREE = BigInteger.valueOf(3);

    public boolean isProbablePrime(BigInteger n, int iterations) {
        if (n.compareTo(ONE) <= 0) return false;
        if (n.equals(TWO) || n.equals(THREE)) return true;
        if (n.mod(TWO).equals(BigInteger.ZERO)) return false; // Even number > 2

        BigInteger d = n.subtract(ONE);
        int r = 0;
        while (d.mod(TWO).equals(BigInteger.ZERO)) {
            d = d.divide(TWO);
            r++;
        }

        Random rand = new Random();
        for (int i = 0; i < iterations; i++) {
            BigInteger a;
            do {
                a = new BigInteger(n.bitLength(), rand);
            } while (a.compareTo(TWO) < 0 || a.compareTo(n.subtract(TWO)) > 0);

            if (!millerTest(n, d, r, a)) {
                return false;
            }
        }
        return true;
    }

    private boolean millerTest(BigInteger n, BigInteger d, int r, BigInteger a) {
        BigInteger x = a.modPow(d, n);

        if (x.equals(ONE) || x.equals(n.subtract(ONE))) {
            return true;
        }

        for (int j = 0; j < r - 1; j++) {
            x = x.modPow(TWO, n);
            if (x.equals(ONE)) {
                return false;
            }
            if (x.equals(n.subtract(ONE))) {
                return true;
            }
        }
        return false;
    }
}