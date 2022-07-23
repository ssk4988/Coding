import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int sum= 0;
        tokenizer =new StringTokenizer(in.readLine());
        for(int i = 0; i < n; i++){
            sum += Integer.parseInt(tokenizer.nextToken());
        }
        int rem = sum % n;
        int pref = sum / n;
        StringBuilder ans = new StringBuilder();
        ans.append(pref);
        ans.append('.');
        for(int i = 0; i < k; i++){
            rem *= 10;
            ans.append(rem / n);
            rem %= n;
        }
        System.out.println(ans);
        in.close();
    }
}