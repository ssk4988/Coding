import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int[] arr = new int[n];
            int[] freq = new int[100005];
            long ans = 0;
            int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
            for(int i = 0; i < n; i++){
                int k = Integer.parseInt(tokenizer.nextToken());
                arr[i] = k;
                min = Math.min(min, k);
                max = Math.max(max, k);
            }
            int diff = max - min;
            for(int i = 0; i < n; i++){
                if(arr[i] - diff >= 1 && arr[i] - diff <= 100000){
                    ans += freq[arr[i] - diff];
                }
                if(diff != 0 && arr[i] + diff >= 1 && arr[i] + diff <= 100000){
                    ans += freq[arr[i] + diff];
                }
                freq[arr[i]]++;
            }
            ans *= 2;
            out.append(ans + "\n");
        }
        System.out.print(out);
        in.close();
    }
}