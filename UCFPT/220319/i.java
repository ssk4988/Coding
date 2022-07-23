import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String s1 = in.readLine();
        String s2 = in.readLine();
        int maxLen = Math.max(s1.length(), s2.length());
        boolean[][] found = new boolean[13][1 << 12];
        int[] a1 = new int[s1.length()];
        int[] a2 = new int[s2.length()];
        for (int i = 0; i < s1.length(); i++) {
            int cur = 0;
            a1[i] = s1.charAt(i) - '0';
            for (int j = i; j >= 0; j--) {
                cur <<= 1;
                cur += a1[i];
                found[i - j + 1][cur] = true;
            }
        }
        for (int i = 0; i < s2.length(); i++) {
            int cur = 0;
            a2[i] = s2.charAt(i) - '0';
            for (int j = i; j >= 0; j--) {
                cur <<= 1;
                cur += a2[i];
                found[i - j + 1][cur] = true;
            }
        }
        iter: for (int i = 1; i < found.length; i++) {
            for (int j = 0; j < (1<<(i)); j++) {
                if (!found[i][j]) {
                    System.out.println(j + " " + i);
                    break iter;
                }
            }

        }

        in.close();
        out.close();
    }
}