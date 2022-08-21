import java.io.*;
import java.util.*;

public class p074 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int[][] coords = new int[n][2];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            coords[i][0] = Integer.parseInt(tokenizer.nextToken());
            coords[i][1] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            int t = Integer.parseInt(tokenizer.nextToken());
            for (int j = 0; j < n; j++) {
                int period = Math.abs(coords[j][0] - coords[j][1]);
                int type = (t / period) % 2 == 0 ? 1 : -1;
                int rem = t % period;
                int slope = coords[j][1] >= coords[j][0] ? 1 : -1;
                int pos = type == 1 ? coords[j][0] + slope * type * rem : coords[j][1] + slope * type * rem;
                if(pos >= x && pos <= y) cnt++;
            }
            System.out.println(cnt);
        }
        in.close();
    }
}