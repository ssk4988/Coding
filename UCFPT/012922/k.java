import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String s = in.readLine();
        int[] count = new int[26];
        int[] last = new int[26];
        boolean works = true;
        Arrays.fill(last, -1);
        for (int i = 0; i < s.length(); i++) {
            count[s.charAt(i) - 'a']++;
            if (count[s.charAt(i) - 'a'] > 2) {
                works = false;
                break;
            }
            if (last[s.charAt(i)-'a']>=0 && (i - last[s.charAt(i) - 'a']) % 2 != 1) {
                works = false;
                break;
            }
            last[s.charAt(i) - 'a'] = i;
        }
        System.out.println(works ? "YES" : "NO");
        in.close();
        out.close();
    }
}