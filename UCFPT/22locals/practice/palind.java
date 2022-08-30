import java.io.*;
import java.util.*;

public class palind {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int p = Integer.parseInt(in.readLine());
        int[] map = new int[26];
        for (int i = 0; i < 26; i++) {
            map[i] = i;
        }
        for (int i = 0; i < p; i++) {
            String s = in.readLine();
            int a = s.charAt(0) - 'a';
            int b = s.charAt(2) - 'a';
            map[a] = b;
            map[b] = a;
        }
        int q = Integer.parseInt(in.readLine());
        for (int j = 0; j < q; j++) {
            String s = in.readLine();
            boolean works = true;
            for (int i = 0; i <= s.length() - 1 - i; i++) {
                int a = s.charAt(i) - 'a';
                int b = s.charAt(s.length() - 1 - i) - 'a';
                if (!(a == b || map[a] == b)) {
                    works = false;
                    break;
                }
            }
            System.out.println(works ? "YES" : "NO");
        }
        in.close();
    }
}