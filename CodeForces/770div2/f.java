import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int q = Integer.parseInt(tokenizer.nextToken());
        int mod = Integer.parseInt(tokenizer.nextToken());
        int[] a = new int[n];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int[] b = new int[n];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            b[i] = Integer.parseInt(tokenizer.nextToken());
        }
        ArrayList<Integer>[][][] bounds = new ArrayList[2][2][n];
        for(int i = 0; i < bounds.length; i++){
            for(int j = 0; j < bounds[i].length; j++){
                for(int k = 0; k < bounds[i][j].length; k++){
                    bounds[i][j][k] = new ArrayList<>();
                }
            }
        }
        for (int i = 0; i < q; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int isA = tokenizer.nextToken().equals("A") ? 0 : 1;
            int start = Integer.parseInt(tokenizer.nextToken()) - 1;
            int end = Integer.parseInt(tokenizer.nextToken()) - 1;
            bounds[isA][0][start].add(start);
            bounds[isA][1][end].add(end);
        }
        Set<Integer> inSetA = new HashSet<>();
        Set<Integer> inSetB = new HashSet<>();
        int offsetA = 0;
        int offsetB = 0;
        for(int i = 0; i < q; i++){

        }
        in.close();
        out.close();
    }

    public static int mod(int num, int mod) {
        if (num >= mod) {
            return num - mod;
        }
        if (num < 0) {
            return num + mod;
        }
        return num;
    }
}