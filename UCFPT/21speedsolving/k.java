import java.io.*;
import java.util.*;

public class k {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        boolean[][] board = new boolean[n][n];
        for(int i = 0; i < n; i++){
            String s = in.readLine();
            for(int j =0; j < n; j++){
                board[i][j] = s.charAt(j) == 'W';
            }
        }
        boolean works = true;
        outer: for(int i = 0; i < n; i++){
            int row = 0;
            int col =0;
            int rcon = 0;
            int ccon = 0;
            for(int j = 0; j < n; j++){
                if(board[i][j]){
                    row++;
                }
                if(board[j][i]){
                    col++;
                }
                if(j == 0){
                    rcon = 1;
                    ccon = 1;
                }
                else{
                    if(board[i][j] == board[i][j-1]) rcon++;
                    else rcon = 1;
                    if(board[j][i] == board[j-1][i]) ccon++;
                    else ccon = 1;
                    if(rcon >= 3 || ccon >= 3){
                        works = false;
                        break outer;
                    }
                }
            }
            if(!(2 * row == n && 2 * col == n)){
                works = false;
                break outer;
            }
        }
        System.out.println(works ? 1 : 0);

        in.close();
        out.close();
    }
}