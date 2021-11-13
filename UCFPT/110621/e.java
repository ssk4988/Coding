/*
ID: ssk49881
LANG: JAVA
TASK: e
*/

import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int count = 0; count < numcases; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            String frac = tokenizer.nextToken();
            String[] fracnum = frac.split("/");
            int numerator = Integer.parseInt(fracnum[0]);
            int denominator = Integer.parseInt(fracnum[1]);
            //System.out.printf("%d %d%n", numerator, denominator);
            ArrayList<Boolean> operations = new ArrayList<>(); // true == went left
            int n2 = numerator;
            int d2 = denominator;
            while (!(n2 == 1 && d2 == 1)) {
                if (n2 > d2) {
                    operations.add(false);
                    n2 -= d2;
                } else {
                    operations.add(true);
                    d2 -= n2;
                }
            }
            int add = 0;
            int base = 1;
            int depth = 0;
            for(int i = operations.size() - 1; i >= 0; i--){
                add *= 2;
                if(!operations.get(i)){
                    add++;
                }
                base*=2;
                depth++;
            }
            System.out.printf("%d %d%n", casenum, base+add);
        }
        in.close();
        out.close();
    }
}