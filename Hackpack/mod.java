import java.io.*;
import java.util.*;

// all operations using modulo

public class mod {
    public static int MOD = 1000000007;

    public static int fastMod(int val) {
        if (val >= MOD)
            val -= MOD;
        return val;
    }

    public static int modInverse(int a) {
        if (a % MOD == 0) {
            return -1; // find better return value
        }
        return power(a, MOD - 2);
    }

    public static int power(int b, int p) {
        if (p == 0)
            return 1;
        if (p == 1)
            return b;
        int res = power(b, p / 2) % MOD;
        res = (res * res) % MOD;
        if (p % 2 == 1) {
            res = (res * b) % MOD;
        }
        return res;
    }
}