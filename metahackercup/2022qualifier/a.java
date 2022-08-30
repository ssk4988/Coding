import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("second_hands_input.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("aoutput.txt")));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            int[] s = new int[n];
            tokenizer = new StringTokenizer(in.readLine());
            boolean works = true;
            HashSet<Integer> c1 = new HashSet<>();
            HashSet<Integer> c2 = new HashSet<>();
            for (int i = 0; i < n && works; i++) {
                s[i] = Integer.parseInt(tokenizer.nextToken());
                if (c1.contains(s[i]) || c1.size() >= k) {
                    if (c2.contains(s[i]) || c2.size() >= k) {
                        works = false;
                    } else {
                        c2.add(s[i]);
                    }
                } else {
                    c1.add(s[i]);
                }
            }
            out.printf("Case #%d: %s\n", (cn + 1), works ? "YES" : "NO");
        }
        in.close();
        out.close();
    }
}