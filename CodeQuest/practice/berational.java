import java.io.*;
import java.util.*;

public class berational {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            String s = in.readLine();
            if (!s.contains(".")) {
                b.append(s + "\n");
                continue;
            }
            int index = s.indexOf(".");
            long numerator = Long.parseLong(s.substring(0, index) + s.substring(index+1));
            long denominator = (long)Math.pow(10, s.length() - index - 1);
            for(int i = 0; i < 10; i++){
                long val = numerator / denominator;
                long tmp = numerator % denominator;
                numerator = denominator;
                denominator = tmp;
                b.append(val + (i + 1 < 10 && tmp != 0 ? " " : ""));
                if(denominator == 0) break;
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}