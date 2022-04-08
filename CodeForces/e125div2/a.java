import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if(x == 0 && y == 0){
                b.append(0 + "\n");
                continue;
            }
            int sqr = x*x + y*y;
            double sqrt = Math.sqrt(sqr);
            int sqrt2 = (int) sqrt;
            if(sqrt2 * sqrt2 == sqr){
                b.append(1 + "\n");
            }
            else{
                b.append(2 + "\n");
            }
        }
        System.out.print(b);
        in.close();
    }
}