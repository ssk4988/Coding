import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int B = Integer.parseInt(tokenizer.nextToken());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            long[] arr = new long[n+1];
            long sum = 0;
            for(int i = 1; i < arr.length; i++){
                if(arr[i-1]+x<=B){
                    arr[i] = arr[i-1]+x;
                }
                else{
                    arr[i] = arr[i-1] - y;
                }
                sum += arr[i];
            }
            b.append(sum + "\n");
        }
        System.out.print(b);
        in.close();
    }
}