import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int[] arr = new int[n];
            int[] num = new int[n+1];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                while(arr[i] > n){
                    arr[i] /= 2;
                }
                while(arr[i] > 0 && num[arr[i]] > 0){
                    arr[i] /= 2;
                }
                num[arr[i]]++;
            }
            boolean works = true;
            for(int i = 1; i <= n; i++){
                if(num[i] != 1) works = false;
            }
            System.out.println(works ? "YES" : "NO");
        }
        in.close();
        out.close();
    }
}