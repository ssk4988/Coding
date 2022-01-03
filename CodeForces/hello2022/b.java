import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] l = new int[n];
            int[] r = new int[n];
            int[] c = new int[n];
            int[] widest = new int[n];
            int[] lowest = new int[n];
            int[] highest = new int[n];
            for (int i = 0; i < n; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                l[i] = Integer.parseInt(tokenizer.nextToken());
                r[i] = Integer.parseInt(tokenizer.nextToken());
                c[i] = Integer.parseInt(tokenizer.nextToken());
                if (i == 0) {
                    continue;
                }
                if (r[i] - l[i] > r[widest[i - 1]] - l[widest[i - 1]]
                        || (r[i] - l[i] == r[widest[i - 1]] - l[widest[i - 1]] && c[i] < c[widest[i - 1]])) {
                    widest[i] = i;
                } else {
                    widest[i] = widest[i - 1];
                }
                if (l[i] < l[lowest[i - 1]] || (l[i] == l[lowest[i - 1]] && c[i] < c[lowest[i - 1]])) {
                    lowest[i] = i;
                } else {
                    lowest[i] = lowest[i - 1];
                }
                if (r[i] > r[highest[i - 1]] || (r[i] == r[highest[i - 1]] && c[i] < c[highest[i - 1]])) {
                    highest[i] = i;
                } else {
                    highest[i] = highest[i - 1];
                }
            }
            for (int i = 0; i < n; i++) {
                int cost = 0;
                if (lowest[i] == highest[i]) {
                    cost = c[lowest[i]];
                } else if (l[lowest[i]] == l[highest[i]] && r[lowest[i]] == r[highest[i]]) {
                    cost = Math.min(c[highest[i]], c[lowest[i]]);
                } 
                else if(l[widest[i]] == l[lowest[i]] && r[widest[i]] == r[highest[i]] && c[widest[i]] < c[lowest[i]] + c[highest[i]]){
                    cost = c[widest[i]];
                }
                else if (l[lowest[i]] == l[highest[i]]) {
                    cost = c[highest[i]];
                } else if (r[lowest[i]] == r[highest[i]]) {
                    cost = c[lowest[i]];
                }
                else {
                    cost = c[lowest[i]] + c[highest[i]];
                }
                b.append(cost + "\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}