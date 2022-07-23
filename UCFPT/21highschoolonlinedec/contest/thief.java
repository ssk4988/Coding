import java.io.*;
import java.util.*;

public class thief {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int casenum = Integer.parseInt(in.readLine());
        for (int i = 0; i < casenum; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int size = Integer.parseInt(tokenizer.nextToken());
            int[] val = new int[size];
            for (int j = 0; j < size; j++) {
                val[j] = Integer.parseInt(tokenizer.nextToken());
            }
            int[][] max = new int[size][2];
            boolean[] set0 = new boolean[size];
            boolean[] set1 = new boolean[size];
            max[0][0] = 0;
            max[0][1] = val[0];
            set1[0] = true;
            for(int j = 1; j < size; j++){
                boolean[] tmp0 = set0;
                boolean[] tmp1 = set1;
                max[j][1] = max[j-1][0] + val[j];
                set1 = tmp0;
                if(max[j-1][0]>max[j-1][1]){
                    max[j][0] = max[j-1][0];
                    set0 = Arrays.copyOf(tmp0, tmp0.length);
                }
                else{
                    max[j][0] = max[j-1][1];
                    set0 = tmp1;
                }
                set1[j] = true;
            }
            int val0 = max[size-1][0];
            int val1 = max[size-1][1];
            int maxNotUsed0 = 0;
            int maxNotUsed1 = 0;
            for(int j = 0; j < size; j++){
                if(!set0[j] && val[j] > maxNotUsed0){
                    maxNotUsed0 = val[j];
                }
                if(!set1[j] && val[j] > maxNotUsed1){
                    maxNotUsed1 = val[j];
                }
            }
            val0 += maxNotUsed0;
            val1 += maxNotUsed1;
            System.out.println(Math.max(val0, val1));
        }

        in.close();
        out.close();
    }
}