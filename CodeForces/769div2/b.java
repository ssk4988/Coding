import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int maxval = n-1;
            int max2 = 1;
            while(max2*2<=maxval){
                max2*=2;
            }
            StringBuilder b = new StringBuilder();
            for(int i = maxval; i >= max2; i--){
                b.append(i + " ");
            }
            for(int i = 0; i < max2; i++){
                b.append(i);
                b.append(i + 1 < max2 ? " " : "\n");
            }
            System.out.print(b);
        }
        in.close();
        out.close();
    }
}