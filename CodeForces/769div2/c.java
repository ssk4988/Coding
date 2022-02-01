import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b= Integer.parseInt(tokenizer.nextToken());
            int c1 = b - a;
            int c2 = 1;
            for(int i = a; i <= b; i++){
                if((i|b)==b){
                    break;
                }
                c2++;
                if(c2 > c1)break;
            }
            int c3 = 1+(a|b)-b;
            int currmin = Math.min(Math.min(c1, c2), c3);
            int c4 = 1;
            for(int i = b; i < Integer.MAX_VALUE; i++){
                if((i|a)==i){
                    break;
                }
                c4++;
                if(c4 > currmin) break;
            }
            System.out.println(Math.min(currmin, c4));
        }
        in.close();
        out.close();
    }
}