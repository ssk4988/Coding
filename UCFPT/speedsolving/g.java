import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] v = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            v[i] = Integer.parseInt(tokenizer.nextToken());
        }
        boolean[] used = new boolean[n];
        int index = 0;
        int left = n;
        while (left > 1) {
            int k = v[index];
            int a = k % left;
            if(a == 0) a = left;
            int cnt = 0;
            while (cnt < a) {
                while (used[index]) {
                    index++;
                    if (index == n)
                        index = 0;
                }
                //now index has label cnt
                if (cnt+1 < a) {
                    index++;
                    if (index == n)
                        index = 0;
                }
                cnt++;
            }
            used[index] = true;
            // System.out.println("eliminated" + (index + 1));
            left--;
            index++;
            if (index == n)
                index = 0;
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                System.out.println(i + 1);
                break;
            }
        }
        in.close();
        out.close();
    }
}