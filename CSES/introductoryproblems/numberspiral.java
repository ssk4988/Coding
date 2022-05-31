import java.io.*;
import java.util.*;

public class numberspiral {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int row = Integer.parseInt(tokenizer.nextToken());
            int col = Integer.parseInt(tokenizer.nextToken());
            long max = Math.max(row, col);
            long ans = max * max;
            if (row >= col) {
                if (row % 2 == 0) {
                    ans -= col - 1;
                } else {
                    ans -= 2 * row - 1 - col;
                }
            } else {
                if(col % 2 == 1){
                    ans -= row - 1;
                }
                else{
                    ans -= 2 * col - 1 - row;
                }
            }
            System.out.println(ans);
        }
        in.close();
    }
}