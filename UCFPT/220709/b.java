import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int[][] op = new int[10][10];
        for (int i = 0; i < 10; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < 10; j++) {
                op[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
        }
        int[][][] tr = new int[10][10][64]; //cur dig, starting dig, 2^x consec digs
        for (int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++){
                tr[i][j][0] = op[i][j];
            }
            
        }
        for (int k = 1; k < 64; k++) {
            for (int i = 0; i < 10; i++) {
                for(int j= 0; j < 10; j++){
                    tr[i][j][k] = tr[tr[i][j][k-1]][(i + (int)((1L << (k - 1)) % 10)) % 10][k - 1];
                }
                
            }
        }
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        String a1 = tokenizer.nextToken();
        long a = Long.parseLong(a1);
        String a2 = tokenizer.nextToken();
        long b = Long.parseLong(a2);
        String ans = "";
        while (a1.length() < a2.length()) {
            a1 = "0" + a1;
        }
        while (a1.length() > a2.length()) {
            a2 = "0" + a2;
        }
        long dist = b - a;
        long cur = 1;
        for (int i = a1.length() - 1; i >= 0; i--) {
            int dig = a1.charAt(i) - '0';
            long times = a >= cur ? dist : ;
            cur *= 10;
            for (int j = 0; (1 << j) <= dist; j++) {
                if (((1 << j) & dist) > 0) {
                    dig = tr[dig][j];
                }
            }
            ans = dig + ans;
        }
        // for (int i = 0; i < a1.length(); i++) {
        // System.out.print(op[a1.charAt(i) - '0'][a2.charAt(i) - '0']);
        // }
        System.out.println(ans);

        in.close();
    }
}