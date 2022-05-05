import java.io.*;
import java.util.*;

public class dna {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            String s = in.readLine();
            for(int i = 0; i< s.length();){
                int val = 0;
                for(int j = 0; j < 7; j++){
                    if(s.charAt(i+j) == 'G' || s.charAt(i+j) == 'C'){
                        val++;
                    }
                    if(j < 6){
val <<= 1;
                    }
                    
                }
                b.append((char)(val));
                i +=7;
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}