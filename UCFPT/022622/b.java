import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numWords = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        tri root = new tri(' ', 0, "");
        for (int i = 0; i < numWords; i++) {
            String word = in.readLine();
            tri curr = root;
            for (int j = 0; j < word.length(); j++) {
                tri next = curr.getChild(word.charAt(j));
                if (next == null) {
                    next = new tri(word.charAt(j), curr.depth + 1, word);
                    curr.children[word.charAt(j) - 'a'] = next;
                }
                curr = next;
            }
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            String word = in.readLine();
            int[] dp = new int[word.length() + 1];
            for (int j = 0; j < dp.length; j++) {
                dp[j] = j;
            }
            tri curr = root.getChild(word.charAt(0));
            for (int j = 1; j < word.length(); j++) {
                dp[j] = Math.min(dp[j - 1] + 1, dp[j]);
                if (curr == null) {
                    dp[dp.length - 1] = dp[j] + (dp.length - 1 - j);
                    break;
                }
                int ndepth = match(curr.target, word, j);
                dp[ndepth] = Math.min(dp[ndepth], dp[j] + 1 + (curr.target.length() - ndepth));
                curr = curr.getChild(word.charAt(j));
            }
            b.append(dp[dp.length - 1]+"\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static int match(String s1, String s2, int start) {
        int sim = start;
        int minsize = Math.min(s1.length(), s2.length());
        while (sim < minsize) {
            if (s1.charAt(sim) == s2.charAt(sim)) {
                sim++;
            } else {
                break;
            }
        }
        return sim;
    }

    public static class tri {
        char val;
        tri[] children = new tri[26];
        int depth = 0;
        String target;

        public tri(char c,int depth, String target) {
            val = c;
            this.depth = depth;
            this.target = target;
        }

        public tri getChild(char c) {
            return children[c - 'a'];
        }
    }
}