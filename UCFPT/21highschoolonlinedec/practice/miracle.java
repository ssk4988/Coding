import java.io.*;
import java.util.*;

public class miracle {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int numtimes = Integer.parseInt(in.readLine());
            double start = 100;
            for(int i = 0; i < numtimes; i++){
                int j = Integer.parseInt(in.readLine());
                double mult = (100 + j) / 100.0;
                start *= mult;
            }
            System.out.printf("%.3f%n", (start - 100));
        }
        in.close();
        out.close();
    }
}