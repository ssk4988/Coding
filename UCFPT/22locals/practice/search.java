import java.io.*;
import java.util.*;

public class search {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int r = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int[][] grid = new int[r][c];
        for (int i = 0; i < r; i++) {
            String s = in.readLine();
            for (int j = 0; j < c; j++) {
                grid[i][j] = s.charAt(j) - 'A';
            }
        }
        int maxLen = 0;
        trie root = new trie(-1);
        int w = Integer.parseInt(in.readLine());
        int[][] ans = new int[w][3]; // r c d
        for (int i = 0; i < w; i++) {
            String s = in.readLine();
            int[] arr = new int[s.length()];
            maxLen = Math.max(maxLen, s.length());
            trie cur = root;
            for (int j = 0; j < s.length(); j++) {
                arr[j] = s.charAt(j) - 'A';
                if (cur.child[arr[j]] == null) {
                    cur.child[arr[j]] = new trie(arr[j]);
                }
                cur = cur.child[arr[j]];
            }
            cur.end = i;
        }
        int[] dx = new int[] { 1, 0, -1, 0 };
        int[] dy = new int[] { 0, 1, 0, -1 };
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (root.child[grid[i][j]] == null)
                    continue;
                t: for (int k = 0; k < 4; k++) {
                    trie start = root;
                    int r1 = i - dx[k];
                    int c1 = j - dy[k];
                    for (int l = 0; l < maxLen; l++) {
                        r1 += dx[k];
                        c1 += dy[k];
                        if (r1 == -1)
                            r1 = r - 1;
                        if (r1 == r)
                            r1 = 0;
                        if (c1 == -1)
                            c1 = c - 1;
                        if (c1 == c)
                            c1 = 0;
                        if (start.child[grid[r1][c1]] == null) {
                            continue t;
                        }
                        start = start.child[grid[r1][c1]];
                        if (start.end != -1) {
                            ans[start.end][0] = i;
                            ans[start.end][1] = j;
                            ans[start.end][2] = k;
                        }
                    }
                }
            }
        }
        char[] d = new char[] { 'D', 'R', 'U', 'L' };
        for (int i = 0; i < w; i++) {
            System.out.println(d[ans[i][2]] + " " + (ans[i][0] + 1) + " " + (ans[i][1] + 1));
        }

        in.close();
    }

    public static class trie {
        int c;
        int end = -1;
        trie[] child = new trie[26];

        public trie(int c) {
            this.c = c;
        }
    }
}