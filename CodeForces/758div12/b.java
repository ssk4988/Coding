import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder str = new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            int max = Math.max(a, b);
            int min = Math.min(a, b);
            if(max > (n-1)/2 || min > (n-2)/2 || max - min > 1){
                str.append(-1 + "\n");
                continue;
            }
            int a2 = a;
            int b2 = b;
            min = 1;
            max = n;
            int[] arr = new int[n];
            boolean[] greater = new boolean[n];
            greater[0] = !(a2>= b2);            
            for(int i = 1; i < greater.length; i++){
                if(a2 > 0 && !greater[i-1]){
                    greater[i] = true;
                    a2--;
                }
                else if(b2 > 0 && greater[i-1]){
                    greater[i] = false;
                    b2--;
                }
                else{
                    greater[i] = greater[i-1];
                }
            }
            for(int i = 0; i < arr.length; i++){
                str.append((greater[i] ? max-- : min++) + (i < n - 1 ? " " : "\n"));
            }
        }
        System.out.print(str);
        in.close();
        out.close();
    }
}