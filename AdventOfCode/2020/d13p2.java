import java.io.*;
import java.util.*;

public class d13p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d13p1.in"));

        int time = Integer.parseInt(in.readLine());
        String data = in.readLine();
        String[] data2 = data.split(",");
        int[] ids = new int[data2.length];
        for (int i = 0; i < data2.length; i++) {
            if (!data2[i].equals("x")) {
                ids[i] = Integer.parseInt(data2[i]);
            } else {
                ids[i] = 1;
            }
        }
        int[] rem = new int[data2.length];
        for (int i = 0; i < rem.length; i++) {
            rem[i] = Math.floorMod(ids[i] - i, ids[i]);
        }
        // System.out.println(Arrays.toString(ids));
        // System.out.println(Arrays.toString(rem));
        long ans = ids[0];
        long num1 = ids[0];
        long inc = ids[0];
        for (int i = 1; i < ids.length; i++) {
            int num2 = ids[i];
            while (ans % num2 != rem[i]) {
                ans += inc;
            }
            inc = lcm(inc, num2);

        }
        System.out.println(ans);

        in.close();
    }

    public static long gcf(long a, long b) {
        if (b > a)
            return gcf(b, a);
        if (b == 0) {
            return a;
        }
        return gcf(b, a % b);
    }

    public static long lcm(long a, long b) {
        return a * b / gcf(a, b);
    }

}
