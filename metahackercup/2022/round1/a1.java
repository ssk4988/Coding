import java.io.*;
import java.util.*;

public class a1 {
    public static void main(String[] args) throws Exception {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("consecutive_cuts_chapter_1_input.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("a1_output.txt")));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder o = new StringBuilder();
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            int[] a = new int[n];
            int[] b = new int[n];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(tokenizer.nextToken());
            }
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                b[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int offset = 0;
            while (offset < n && b[offset] != a[0]) { // CHECK IN A2
                offset++;
            }
            boolean isRotation = true;
            for (int i = 0; i < n; i++) {
                if (a[i] != b[(offset + i) % n]) {
                    isRotation = false;
                }
            }
            boolean works = isRotation;
            if (works) {
                if (k == 0 && offset != 0) {
                    works = false;
                }
                if (k == 1 && offset == 0) {
                    works = false;
                }
                if (n == 2 && offset != k % 2) {
                    works = false;
                }
            }
            o.append("Case #" + (cn + 1) + ": " + (works ? "YES" : "NO") + "\n");
        }
        out.print(o);
        in.close();
        out.close();
    }
}