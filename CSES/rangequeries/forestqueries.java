import java.io.*;
import java.util.*;

public class forestqueries {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        int[][] arr = new int[size][size];
        int[][] prefix = new int[size][size];
        for (int i = 0; i < size; i++) {
            String s = in.readLine();
            for (int j = 0; j < size; j++) {
                prefix[i][j] = arr[i][j] = s.charAt(j) == '*' ? 1 : 0;
                if (i > 0)
                    prefix[i][j] += prefix[i - 1][j];
                if (j > 0)
                    prefix[i][j] += prefix[i][j - 1];
                if (i > 0 && j > 0)
                    prefix[i][j] -= prefix[i - 1][j - 1];
            }
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int y1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int x2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int y2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int ans = prefix[x2][y2];
            if (x1 > 0)
                ans -= prefix[x1 - 1][y2];
            if (y1 > 0)
                ans -= prefix[x2][y1 - 1];
            if (x1 > 0 && y1 > 0)
                ans += prefix[x1 - 1][y1 - 1];
            b.append(ans + "\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}