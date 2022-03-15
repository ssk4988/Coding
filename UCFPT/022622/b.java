import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numWords = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        let root = new let(' ', null, "");
        for (int i = 0; i < numWords; i++) {
            String word = in.readLine();
            let curr = root;
            for (int j = 0; j < word.length(); j++) {
                let next = curr.getChild(word.charAt(j));
                if (next == null) {
                    next = new let(word.charAt(j), curr, word);
                    curr.children[word.charAt(j) - 'a'] = next;
                }
                curr = next;
            }
        }
        for (int i = 0; i < numQueries; i++) {
            String word = in.readLine();
            int[] dp = new int[word.length() + 1];
            for (int j = 0; j < dp.length; j++) {
                dp[j] = j;
            }
            let curr = root.getChild(word.charAt(0));
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
            System.out.println(dp[dp.length - 1]);
        }
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

    public static class let {
        char val;
        let parent;
        let[] children = new let[26];
        int depth = 0;
        String target;

        public let(char c, let parent, String target) {
            val = c;
            this.parent = parent;
            if (parent != null) {
                depth = parent.depth + 1;
            }
            this.target = target;
        }

        public let getChild(char c) {
            return children[c - 'a'];
        }
    }
}