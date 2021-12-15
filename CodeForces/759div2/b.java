import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int len =Integer.parseInt(in.readLine());
            int[] arr = new int[len];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < len; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int num = 0;
            int curr = arr[len - 1];
            for(int i = len - 1; i >= 0; i--){
                if(arr[i] > curr){
                    num++;
                    curr = arr[i];
                }
            }
            System.out.println(num);
        }

        in.close();
        out.close();
    }
}