import java.io.*;
import java.util.*;

public class worm {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int row = Integer.parseInt(tokenizer.nextToken());
            int col = Integer.parseInt(tokenizer.nextToken());
            char[][] board = new char[row][col];
            for (int i = 0; i < row; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < col; j++) {
                    board[i][j] = tokenizer.nextToken().charAt(0);
                }
            }
            int nwords = Integer.parseInt(in.readLine());
            iter: for (int i = 0; i < nwords; i++) {
                String s = in.readLine();
                for (int x = 0; x < board.length; x++) {
                    for (int y = 0; y < board[x].length; y++) {
                        if (solve(s, 0, x, y, board)) {
                            b.append(s + "\n");
                            continue iter;
                        }
                    }
                }
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static boolean solve(String s, int depth, int r, int c, char[][] board) {
        if (depth == s.length()) {
            return true;
        }
        if (s.charAt(depth) != board[r][c])
            return false;

        int[] dx = new int[]{1, 1, 1, 0, 0, -1, -1, -1};
        int[] dy = new int[]{-1, 0, 1, 1, -1, -1, 0, 1};
        for(int i = 0; i < dx.length; i++){
            if(r + dx[i] >= 0 && r + dx[i] < board.length && c + dy[i] >= 0 && c + dy[i] < board[0].length){
                if(solve(s, depth+1, r+dx[i], c+dy[i], board)) return true;
            }
        }
        return false;
    }
}