import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            long alice = Long.parseLong(tokenizer.nextToken());
            long[] arr = new long[n];
            long target = Long.parseLong(tokenizer.nextToken());
            long numone = ((alice & 1) == 1) ? 1 : 0;
            tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                arr[i] = Long.parseLong(tokenizer.nextToken());
                if((arr[i]&1)==1){
                    numone++;
                }
            }
            numone%=2;
            if(numone==(target&1)){
                System.out.println("Alice");
            }
            else{
                System.out.println("Bob");
            }
        }

        in.close();
        out.close();
    }
}