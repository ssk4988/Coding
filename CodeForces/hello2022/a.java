import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            if(n - k >= n / 2){
                int k2 = k;
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        if(i == j && i % 2 == 0 && k2 > 0){
                            System.out.print("R");
                            k2--;
                        }
                        else{
                            System.out.print(".");
                        }
                    }
                    System.out.println();
                }
            }
            else{
                System.out.println(-1);
            }
        }

        in.close();
        out.close();
    }
}