import java.io.*;
import java.util.*;

public class prob2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int p = Integer.parseInt(in.readLine());
            int[] ps = new int[p];
            for (int i = 0; i < p; i++) {
                String s = in.readLine().substring(1);
                ps[i] = Integer.parseInt(s.substring(0, s.indexOf('.')) + s.substring(s.indexOf('.') + 1));
            }
            // System.out.println(Arrays.toString(ps));
            Arrays.sort(ps);
            long answer = 0;
            for (int i = 0; i + 2 < p; i++) {
                int j = i + 1;
                int k = p - 1;
                while (j < k) {
                    if (ps[i] + ps[j] + ps[k] == 50000) {
                        answer++;
                        j++;
                    } else if (ps[i] + ps[j] + ps[k] < 50000) {
                        j++;
                    } else if (ps[i] + ps[j] + ps[k] > 50000) {
                        k--;
                    }
                }
            }
            System.out.println(answer);
        }

        in.close();
        out.close();
    }
}