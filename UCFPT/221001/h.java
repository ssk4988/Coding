import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());

        boolean[] abset = new boolean[2];
        boolean[] ab = new boolean[2];
        boolean[] ewset = new boolean[n];
        boolean[] ew = new boolean[n];
        for (int i = 0; i < k; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            String s1 = tokenizer.nextToken();
            char c = s1.charAt(0);
            String s = tokenizer.nextToken();
            boolean dir = s.charAt(0) == 'S' || s.charAt(0) == 'W'; // true for S2N or W2E
            if (c == 'A' || c == 'B') {
                int ind = c == 'A' ? 0 : 1;
                abset[ind] = true;
                ab[ind] = dir;
            } else {
                int ind = Integer.parseInt(s1) - 1;
                ewset[ind] = true;
                ew[ind] = dir;
            }
        }
        int notsetmid = 0;
        for (int i = 1; i < n - 1; i++) {
            if (!ewset[i])
                notsetmid++;
        }
        long ways = 0;
        if ((!abset[0] || ab[0]) && (!abset[1] || ab[1]) && n % 2 == 1) {
            // both north
            boolean works = true;
            boolean toeast = true;
            for (int i = 0; i < n; i++) {
                if (!ewset[i] || ew[i] == toeast) {

                } else {
                    works = false;
                    break;
                }
                toeast = !toeast;
            }
            if (works)
                ways += 1;
        }
        if (((abset[0] && !ab[0]) || !abset[0]) && ((abset[1] && !ab[1]) || !abset[1]) && n % 2 == 1) {
            // both south
            boolean works = true;
            boolean toeast = false;
            for (int i = 0; i < n; i++) {
                if (!ewset[i] || ew[i] == toeast) {

                } else {
                    works = false;
                    break;
                }
                toeast = !toeast;
            }
            if (works)
                ways += 1;
        }
        if (((abset[0] && ab[0]) || !abset[0]) &&
                ((abset[1] && !ab[1]) || !abset[1]) &&
                ((ewset[0] && !ew[0]) || !ewset[0]) &&
                ((ewset[n - 1] && ew[n - 1]) || !ewset[n - 1])) {
            // a north b south
            ways += (1L << notsetmid);
        }
        if (((abset[0] && !ab[0]) || !abset[0]) &&
                ((abset[1] && ab[1]) || !abset[1]) &&
                ((ewset[0] && ew[0]) || !ewset[0]) &&
                ((ewset[n - 1] && !ew[n - 1]) || !ewset[n - 1])) {
            // a south b north
            ways += (1L << notsetmid);
        }
        System.out.println(ways);
        in.close();
    }
}