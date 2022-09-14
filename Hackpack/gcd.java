import java.io.*;
import java.util.*;

public class gcd {
    public static int calc_gcd(int a, int b) {
        if (b == 0)
            return a;
        return calc_gcd(b, a % b);
    }
}