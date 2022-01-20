import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            long[] t = new long[n];
            long[] h = new long[n];
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                t[i] = Integer.parseInt(tokenizer.nextToken());
            }
            tokenizer = new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                h[i] = Integer.parseInt(tokenizer.nextToken());
            }
            long mana = 0;
            int index = 0;
            while(index < n){
                long start = t[index] - h[index];
                long end = t[index];
                for(int i = index+1; i < n; i++){
                    if(t[i] - h[i] < start){
                        start = t[i] - h[i];
                        end = t[i];
                        index = i;
                    }
                    else if(t[i] - end < h[i]){
                        end = t[i];
                        index = i;
                    }
                }
                mana += (end - start + 1) * (end - start) / 2;
                index++;
            }
            System.out.println(mana);
        }
        in.close();
        out.close();
    }
}