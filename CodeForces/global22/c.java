import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean[][][] even = new boolean[105][105][2];//even odd e1o0
        even[0][1][1] = false;
        even[0][1][0] = true;
        even[1][0][1] = true;
        even[1][0][0] = false;
        even[0][2][1] = false;
        even[0][2][0] = true;
        even[1][1][1] = true;
        even[1][1][0] = true;
        even[2][0][1] = true;
        even[2][0][0] = false;
        even[0][0][1] = true;
        even[0][0][0] = false;
        for(int i = 3; i < even.length; i++){
            for(int j = 0; j <= i; j++){
                int k = i - j;
                boolean left = false;
                boolean right = false;
                if(k - 1 >= 0){
                    left = true;
                    if(k - 2 >= 0){
                        left &= even[j][k-2][0];
                    }
                    if(j - 1 >= 0){
                        left &= even[j-1][k-1][0];
                    }
                }
                if(j - 1 >= 0){
                    right = true;
                    if(k -1 >= 0){
                        right &= even[j-1][k-1][1];
                    }
                    if(j - 2 >= 0){
                        right &= even[j-2][k][1];
                    }
                }
                even[j][k][1] = left || right;

                left = right = false;
                if(k - 1 >= 0){
                    left = true;
                    if(k - 2 >= 0){
                        left &= even[j][k-2][1];
                    }
                    if(j - 1 >= 0){
                        left &= even[j-1][k-1][1];
                    }
                }
                if(j - 1 >= 0){
                    right = true;
                    if(k -1 >= 0){
                        right &= even[j-1][k-1][0];
                    }
                    if(j - 2 >= 0){
                        right &= even[j-2][k][0];
                    }
                }
                even[j][k][0] = left || right;
            }
        }
        StringBuilder out = new StringBuilder();
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            int e = 0;
            int o = 0;
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            for(int i = 0; i < n; i++){
                int k = Integer.parseInt(tokenizer.nextToken());
                if(k % 2 == 0) e++;
                else o++;
            }
            out.append(even[e][o][1] ? "Alice\n" : "Bob\n");
        }
        System.out.print(out);
        in.close();
    }
}