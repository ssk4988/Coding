import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int p = Integer.parseInt(tokenizer.nextToken());
            int[] arr = new int[4];
            int win = -1;
            for(int i = 0; i < 4; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken());
                if(arr[i] <= p && (win == -1 || p - arr[i] < p - arr[win])){
                    win = i;
                }
            }
            System.out.println(win + 1);
        }
        in.close();
        out.close();
    }
}