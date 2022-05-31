import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            int c= 1;
            for(int i = 1; i <= n; i++){
                c *= i;
                c %= 10;
            }
            System.out.println(c);
        }
        in.close();
    }
}