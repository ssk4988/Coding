import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            long w = Integer.parseInt(tokenizer.nextToken());
            long h = Integer.parseInt(tokenizer.nextToken());
            long[][] coords = new long[4][];
            for(int i = 0; i < coords.length; i++){
                tokenizer = new StringTokenizer(in.readLine());
                int k = Integer.parseInt(tokenizer.nextToken());
                coords[i] = new long[k];
                for(int j = 0; j < k; j++){
                    coords[i][j] = Integer.parseInt(tokenizer.nextToken());
                }
                Arrays.sort(coords[i]);
            }
            long answer = Math.max(Math.max((coords[0][coords[0].length-1] - coords[0][0]) * h, (coords[1][coords[1].length-1] - coords[1][0]) * h), Math.max((coords[2][coords[2].length-1] - coords[2][0]) * w, (coords[3][coords[3].length-1] - coords[3][0]) * w));
            System.out.println(answer);
        }
        in.close();
        out.close();
    }
}