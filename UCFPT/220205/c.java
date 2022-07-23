import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int r = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int v = Integer.parseInt(tokenizer.nextToken());
        int h = Integer.parseInt(tokenizer.nextToken());
        boolean[][] black = new boolean[v][h];
        black[0][0] = true;
        for(int i = 0; i < v; i++){
            for(int j = 0; j < h; j++){
                if(i == 0 && j == 0) continue;
                if(i == 0) black[i][j] = !black[i][j-1];
                else{
                    black[i][j] = !black[i-1][j];
                }
            }
        }
        int[] rs = new int[v];
        int[] cs =new int[h];
        for(int i = 0; i < v; i++){
            rs[i] = Integer.parseInt(in.readLine());
        }
        for(int i = 0; i < h; i++){
            cs[i] = Integer.parseInt(in.readLine());
        }
        for(int i = 0; i < v; i++){
            StringBuilder b= new StringBuilder();
            for(int j = 0; j < h; j++){
                for(int k = 0; k < cs[j]; k++){
                    b.append(black[i][j] ? 'B' : 'W');
                }
            }
            for(int k = 0; k < rs[i]; k++){
                System.out.println(b);
            }
        }

        in.close();
        out.close();
    }
}