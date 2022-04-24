import java.io.*;
import java.util.*;

public class checkmate {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int[][] board = new int[8][8]; // 2 p 3 n 5 b 7 r 11 q 13 k
            int[][] king = new int[2][2];
            for (int i = 0; i < 8; i++) {
                String s = in.readLine();
                for (int j = 0; j < 8; j++) {
                    if (s.charAt(j) == '.') {
                        board[i][j] = 0;
                    } else if (s.charAt(j) == 'P') {
                        board[i][j] = 2;
                    } else if (s.charAt(j) == 'p') {
                        board[i][j] = 4;
                    } else if (s.charAt(j) == 'N') {
                        board[i][j] = 3;
                    } else if (s.charAt(j) == 'n') {
                        board[i][j] = 9;
                    } else if (s.charAt(j) == 'B') {
                        board[i][j] = 5;
                    } else if (s.charAt(j) == 'b') {
                        board[i][j] = 25;
                    } else if (s.charAt(j) == 'R') {
                        board[i][j] = 7;
                    } else if (s.charAt(j) == 'r') {
                        board[i][j] = 49;
                    } else if (s.charAt(j) == 'Q') {
                        board[i][j] = 11;
                    } else if (s.charAt(j) == 'q') {
                        board[i][j] = 121;
                    } else if (s.charAt(j) == 'K') {
                        board[i][j] = 13;
                        king[0][0] = i;
                        king[0][1] = j;
                    } else if (s.charAt(j) == 'k') {
                        board[i][j] = 169;
                        king[1][0] = i;
                        king[1][1] = j;
                    }
                }
            }
            int[][][] capture = new int[2][8][8];
            int state = 0;
            int[] ndx = new int[] { 2, 2, -2, -2, 1, 1, -1, -1 };
            int[] ndy = new int[] { 1, -1, 1, -1, 2, -2, 2, -2 };
            int[] bdx = new int[] { 1, 1, -1, -1 };
            int[] bdy = new int[] { 1, -1, 1, -1 };
            int[] rdx = new int[] { 1, 0, -1, 0 };
            int[] rdy = new int[] { 0, 1, 0, -1 };
            int[] kdx = new int[] { 0, 1, 1, 1, 0, -1, -1, -1 };
            int[] kdy = new int[] { 1, 1, 0, -1, -1, -1, 0, 1 };
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j] == 0) {

                    } else if (board[i][j] % 2 == 0) {
                        if (board[i][j] == 2) {
                            if (j > 0)
                                capture[0][i - 1][j - 1] = board[i][j];
                            if (j + 1 < board[i].length)
                                capture[0][i - 1][j + 1] = board[i][j];
                        } else {
                            if (j > 0)
                                capture[0][i + 1][j - 1] = board[i][j];
                            if (j + 1 < board[i].length)
                                capture[0][i + 1][j + 1] = board[i][j];
                        }
                    } else if (board[i][j] % 3 == 0) {
                        capture(board, i, j, capture, ndx, ndy, 1);
                    } else if (board[i][j] % 5 == 0) {
                        capture(board, i, j, capture, bdx, bdy, 10);
                    } else if (board[i][j] % 7 == 0) {
                        capture(board, i, j, capture, rdx, rdy, 10);
                    } else if (board[i][j] % 11 == 0) {
                        capture(board, i, j, capture, bdx, bdy, 10);
                        capture(board, i, j, capture, rdx, rdy, 10);
                    } else if (board[i][j] % 13 == 0) {
                        capture(board, i, j, capture, kdx, kdy, 1);
                    }

                }
            }
            for(int p = 0; p< 2; p++){
                int i = king[1-p][0];
                int j = king[1-p][1];
                if(capture[p][i][j] != 0){
                    boolean surround = true;
                    for (int k = 0; k < kdx.length; k++) {
                        if (kdx[k] + j < board[i].length && kdx[k] + j >= 0 && kdy[k] + i < board.length
                                && kdy[k] + i >= 0) {
                            if (capture[p][kdy[k] + i][kdx[k] + j] == 0 && board[kdy[k] + i][kdx[k] + j] == 0) {
                                surround = false;
                            }
                        }
                    }
                    if(surround){
                        state = p == 0 ? 1 : -1;
                        break;
                    }
                }
            }
            if (state == 0) {
                b.append("NO CHECKMATE\n");
            } else if (state == 1) {
                b.append("CHECKMATE WHITE\n");
            } else {
                b.append("CHECKMATE BLACK\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static void capture(int[][] board, int i, int j, int[][][] capture, int[] dx, int[] dy, int range) {

        boolean black = board[i][j] == 4 || board[i][j] == 9 || board[i][j] == 25 || board[i][j] == 49 || board[i][j] == 121 || board[i][j] == 169;

        for (int k = 0; k < dx.length; k++) {
            int l = 1;
            while (l <= range && dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                    && dy[k] * l + i >= 0) {
                // if(board[dy[k]*l+i][dx[k]*l+j]!=0)

                capture[black ? 1 : 0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                if (board[dy[k] * l + i][dx[k] * l + j] != 0) {
                    break;
                }
                l++;
            }
        }
    }
}