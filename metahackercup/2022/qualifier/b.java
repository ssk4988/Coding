import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("second_friend_input.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("boutput.txt")));
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int r = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            boolean[][] tree = new boolean[r][c];
            int cnt = 0;
            for (int i = 0; i < r; i++) {
                String s = in.readLine();
                for (int j = 0; j < c; j++) {
                    tree[i][j] = s.charAt(j) == '^';
                    if (tree[i][j])
                        cnt++;
                }
            }
            boolean works = (r > 1 && c > 1) || cnt <= 0;
            out.printf("Case #%d: %s\n", (cn + 1), works ? "Possible" : "Impossible");
            if (works) {
                StringBuilder s = new StringBuilder();
                for (int i = 0; i < c; i++) {
                    s.append(cnt <= 0 ? '.' : '^');
                }
                for (int i = 0; i < r; i++) {
                    out.println(s);
                }
            }
        }
        in.close();
        out.close();
    }
}