import java.io.*;
import java.util.*;

public class m {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int row = Integer.parseInt(tokenizer.nextToken());
        int col = Integer.parseInt(tokenizer.nextToken());
        boolean[][] c = new boolean[row][col];boolean[][] a = new boolean[row][col];
        boolean[][] b = new boolean[row][col];
        for (int i = 0; i < row; i++) {
            String s = in.readLine();
            for (int j = 0; j < col; j++) {
                c[i][j] = a[i][j] = b[i][j] = s.charAt(j) == '1';
            }
        }
        for(int i = 0; i < row; i++){
            a[i][0] = true;
            b[i][col - 1] = true;
            for(int j = 1; j < col - 1; j++){
                if(i % 2 == 0){
                    a[i][j] = true;
                }
                else{
                    b[i][j] = true;
                }
            }
        }
        StringBuilder out = new StringBuilder();
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                out.append(a[i][j] ? 1 : 0);
            }
            out.append("\n");
        }
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                out.append(b[i][j] ? 1 : 0);
            }
            out.append("\n");
        }
        System.out.print(out);

        in.close();
    }
}