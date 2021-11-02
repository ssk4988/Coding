/*
ID: ssk49881
LANG: JAVA
TASK: numtri
*/

import java.io.*;
import java.util.*;

public class numtri {
    public static int[][] pyramid;
    public static int[][] sums;
    public static int r;
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("numtri.in"));
        PrintWriter out = new PrintWriter(new File("numtri.out"));
        r = Integer.parseInt(in.nextLine());
        pyramid = new int[r][];
        sums = new int[r][];
        for(int i =0;i<r;i++){
            pyramid[i] = new int[i + 1];
            sums[i] = new int[i + 1];
            String[] phrase = in.nextLine().split(" ");
            for(int j = 0; j < i + 1; j++){
                pyramid[i][j] = Integer.parseInt(phrase[j]);
            }
            Arrays.fill(sums[i], -5);
        }
        int sum = dfs(0, 0);
        out.println(sum);


        in.close();
        out.close();
    }
    public static int dfs(int depth, int index){
        if(depth == r - 1){
            return pyramid[depth][index];
        }
        if(sums[depth][index] != -5){
            return sums[depth][index];
        }
        sums[depth][index] = pyramid[depth][index] + Math.max(dfs(depth + 1, index), dfs(depth + 1, index + 1));
        return sums[depth][index];
    }
}