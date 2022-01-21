import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken());
            int b = Integer.parseInt(tokenizer.nextToken());
            int c = Integer.parseInt(tokenizer.nextToken());
            if((b - (c - b) > 0 && (b - (c - b)) % a == 0)||((c + a) % 2 == 0 && ((c + a) / 2) % b == 0)||(b + (b - a) > 0 && (b + (b - a)) % c == 0)){
                System.out.println("YES");
            }
            else{
                System.out.println("NO");
            }
        }

        in.close();
        out.close();
    }
}