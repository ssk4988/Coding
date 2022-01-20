import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            String s = in.readLine();
            int[] occ = new int[26];
            for(int i = 0; i < s.length(); i++){
                occ[s.charAt(i) - 'a']++;
            }
            for(int i = 0; i < occ.length; i++){
                for(int j = 0; j < occ[i]; j++){
                    b.append((char)('a' + i));
                }
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}