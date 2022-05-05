import java.io.*;
import java.util.*;

public class hamming {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        int[] bits = new int[30];
        bits[0] = 1;
        StringBuilder b = new StringBuilder();
        int[] diff = new int[bits.length - 1];
        for (int i = 1; i < bits.length; i++) {
            bits[i] = bits[i - 1] * 2;
        }
        for (int i = 1; i < diff.length; i++) {
            diff[i] = bits[i + 1] - bits[i] + diff[i - 1] - 1;
        }

        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            for (int i = 0; i < n; i++) {
                String s = in.readLine();
                int len = s.length();
                int numParity = 0;
                while (diff[numParity] < len) {
                    numParity++;
                }
                numParity++;
                boolean[] code = new boolean[numParity + len + 1];
                boolean[] isParity = new boolean[numParity + len + 1];
                for (int j = 0; j < bits.length; j++) {
                    if (bits[j] < isParity.length) {
                        isParity[bits[j]] = true;
                    }
                }
                int cnt = 0;
                for(int j = 1; j < code.length; j++){
                    if(!isParity[j]){
                        code[j] = s.charAt(cnt++) == '1';
                    }
                }
                for (int j = 1; j < code.length; j++) {
                    if(isParity[j]){
                        for(int k= j; k < code.length; k++){
                            if(!isParity[k] && (k & j) > 0){
                                //System.out.println(k + " " + j);
                                code[j] ^= code[k];
                            }
                        }
                    }
                }
                //System.out.print("");
                for(int j = 1; j < code.length; j++){
                    if(code[j]){
                        b.append('1');
                    }
                    else{
                        b.append('0');
                    }
                }
                b.append("\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}