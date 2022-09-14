import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class a2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new
        // FileReader("consecutive_cuts_chapter_1_input.txt"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new
        // FileWriter("a1_output.txt")));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder o = new StringBuilder();
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            int[] a = new int[n];
            int[] b = new int[n];
            tokenizer = new StringTokenizer(in.readLine());
            Map<Integer, ArrayList<Integer>> amap = new HashMap<>();
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(tokenizer.nextToken());
                if(!amap.containsKey(a[i])){
                    amap.put(a[i], new ArrayList<>());
                }
                amap.get(a[i]).add(i);
            }
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++) {
                b[i] = Integer.parseInt(tokenizer.nextToken());
            }
            boolean[] checked = new boolean[n];
            ArrayList<Integer> offset = new ArrayList<>();
            /*
            int test = 0;
            while (test < n && offset.size() < 3) {
                if (b[test] != a[0]) {
                    test++;
                } else {
                    boolean isRotation = true;
                    for (int i = 0; i < n; i++) {
                        if (a[i] != b[(offset + i) % n]) {
                            isRotation = false;
                        }
                    }
                }

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
            */
        }
        out.print(o);
        in.close();
        out.close();
    }
}