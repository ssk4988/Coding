import java.io.*;
import java.util.*;

public class freq {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int[][] freq = new int[30][26];
        int n = Integer.parseInt(in.readLine());
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            String s = in.readLine();
            maxLen = Math.max(maxLen, s.length());
            for (int j = 0; j < s.length(); j++) {
                freq[j][s.charAt(j) - 'a']++;
            }
        }
        for (int i = 0; i < maxLen; i++) {
            ArrayList<Integer> best = new ArrayList<>();
            best.add(0);
            for (int j = 1; j < 26; j++) {
                if (freq[i][j] > freq[i][best.get(0)]) {
                    best = new ArrayList<>();
                    best.add(j);
                } else if (freq[i][j] == freq[i][best.get(0)]) {
                    best.add(j);
                }
            }
            System.out.print((i + 1) + ":");
            for (int j : best) {
                System.out.print(" " + (char) (j + 'a'));
            }
            System.out.println();
        }
    }
}