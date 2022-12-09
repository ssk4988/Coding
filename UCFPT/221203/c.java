import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
public class c{
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        //check t == 0 and smaller than some or all student health
        int n = Integer.parseInt(tokenizer.nextToken());
        int t = Integer.parseInt(tokenizer.nextToken());
        long[] s = new long[n];
        long[] ans = new long[n];
        for(int i = 0; i < n; i++){
            s[i] = Integer.parseInt(in.readLine());
        }
        long start = 0;
        long end = t;
        ans[0] = t / s[0];
        end = start + ans[0] * s[0];
        start += s[0];
        long period = s[0];
        for(int i = 1; i < n; i++){
            if(ans[i - 1] == 0) break;
            if(s[i] > period){
                ans[i] = (t - start) / s[i];
                end = start + ans[i] * s[i];
                period = s[i];
            }
            else{
                ans[i] = ans[i - 1] - 1;
                if(t - end >= s[i]){
                    ans[i]++;
                }
                if(ans[i] > 0){
                    end = start + (ans[i] - 1) * period + s[i];
                }
                // end += s[i];
                // if(ans[i] < ans[i - 1]){
                //     end -= period;
                // }
            }
            start += s[i];
        }
        for(int i = 0; i < n; i++){
            System.out.println(ans[i] + 1);
        }
    }
}