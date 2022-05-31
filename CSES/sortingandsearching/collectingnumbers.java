import java.io.*;
import java.util.*;

public class collectingnumbers {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int cnt = n;
        boolean[] set = new boolean[n+1];
        for (int i = 0; i < n; i++) {
            int j = Integer.parseInt(tokenizer.nextToken());
            if (set[j-1]) {
                cnt--;
            }
            set[j]=true;
        }
        System.out.println(cnt);
        in.close();
    }
}