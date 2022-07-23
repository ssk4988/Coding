import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for (int cn = 0; cn < nc; cn++) {
            int[][] arr = new int[2][2];
            int[] x = new int[2];
            int[] y = new int[2];
            int cnt = 0;
            for (int i = 0; i < 2; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < 2; j++) {
                    arr[i][j] = Integer.parseInt(tokenizer.nextToken());
                    x[i] += arr[i][j];
                    y[j] += arr[i][j];
                    cnt += arr[i][j];
                }
            }

            int ans = 0;
            if (cnt == 0)
                ans = 0;
            else if (cnt < 4)
                ans = 1;
            else
                ans = 2;
            b.append(ans + "\n");
        }
        System.out.print(b);
        in.close();
    }
}