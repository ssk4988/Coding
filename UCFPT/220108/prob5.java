import java.io.*;
import java.util.*;

public class prob5 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            double answer = 0;
            if(n == 1){
                answer = 1;
            }
            else{
                answer = Math.pow((double)(k - 1) / k, n - 1);
            }
            System.out.printf("%.3f\n", answer);
        }

        in.close();
        out.close();
    }
}