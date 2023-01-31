import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int w = Integer.parseInt(tokenizer.nextToken());
            int d = Integer.parseInt(tokenizer.nextToken());
            int h = Integer.parseInt(tokenizer.nextToken());
            tokenizer = new StringTokenizer(in.readLine());
            int b = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            int f = Integer.parseInt(tokenizer.nextToken());
            int g = Integer.parseInt(tokenizer.nextToken());
            int ans = Integer.MAX_VALUE;
            ans = Math.min(ans, b + f + Math.abs(g - c));
            ans = Math.min(ans, c + g + Math.abs(b - f));
            ans = Math.min(ans, w - b + w - f + Math.abs(g - c));
            ans = Math.min(ans, d - c + d - g + Math.abs(b - f));
            ans += h;
            System.out.println(ans);
        }
        in.close();
    }
}
