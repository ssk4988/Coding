import java.io.*;
import java.util.*;

public class checkmate {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
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
                        int[] dx = new int[] { 2, 2, -2, -2, 1, 1, -1, -1 };
                        int[] dy = new int[] { 1, -1, 1, -1, 2, -2, 2, -2 };
                        for (int k = 0; k < dx.length; k++) {
                            if (dx[k] + j < board[i].length && dx[k] + j >= 0 && dy[k] + i < board.length
                                    && dy[k] + i >= 0) {
                                if (board[i][j] == 3) {
                                    capture[0][dy[k] + i][dx[k] + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] + i][dx[k] + j] = board[i][j];
                                }
                            }
                        }
                    } else if (board[i][j] % 5 == 0) {
                        int[] dx = new int[] { 1, 1, -1, -1 };
                        int[] dy = new int[] { 1, -1, 1, -1 };
                        for (int k = 0; k < dx.length; k++) {
                            int l = 1;
                            while (dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                                    && dy[k] * l + i >= 0) {
                                if (board[i][j] == 5) {
                                    capture[0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                }
                                l++;
                            }
                        }
                    } else if (board[i][j] % 7 == 0) {
                        int[] dx = new int[] { 1, 0, -1, 0 };
                        int[] dy = new int[] { 0, 1, 0, -1 };
                        for (int k = 0; k < dx.length; k++) {
                            int l = 1;
                            while (dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                                    && dy[k] * l + i >= 0) {
                                if (board[i][j] == 7) {
                                    capture[0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                }
                                l++;
                            }
                        }
                    } else if (board[i][j] % 11 == 0) {
                        int[] dx = new int[] { 1, 1, -1, -1 };
                        int[] dy = new int[] { 1, -1, 1, -1 };
                        for (int k = 0; k < dx.length; k++) {
                            int l = 1;
                            while (dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                                    && dy[k] * l + i >= 0) {
                                if (board[i][j] == 11) {
                                    capture[0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                }
                                l++;
                            }
                        }
                        dx = new int[] { 1, 0, -1, 0 };
                        dy = new int[] { 0, 1, 0, -1 };
                        for (int k = 0; k < dx.length; k++) {
                            int l = 1;
                            while (dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                                    && dy[k] * l + i >= 0) {
                                if (board[i][j] == 11) {
                                    capture[0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                                }
                                l++;
                            }
                        }
                    } else if (board[i][j] % 13 == 0) {
                        int[] dx = new int[] { 0, 1, 1, 1, 0, -1, -1, -1 };
                        int[] dy = new int[] { 1, 1, 0, -1, -1, -1, 0, 1 };
                        for (int k = 0; k < dx.length; k++) {
                            if (dx[k] + j < board[i].length && dx[k] + j >= 0 && dy[k] + i < board.length
                                    && dy[k] + i >= 0) {
                                if (board[i][j] == 13) {
                                    capture[0][dy[k] + i][dx[k] + j] = board[i][j];
                                } else {
                                    capture[1][dy[k] + i][dx[k] + j] = board[i][j];
                                }
                            }
                        }
                    }

                }
            }
            System.out.print("");
            if (capture[0][king[1][0]][king[1][1]] != 0) {
                int i = king[1][0];
                int j = king[1][1];
                int[] dx = new int[] { 0, 1, 1, 1, 0, -1, -1, -1 };
                int[] dy = new int[] { 1, 1, 0, -1, -1, -1, 0, 1 };
                boolean surround = true;
                for (int k = 0; k < dx.length; k++) {
                    if (dx[k] + j < board[i].length && dx[k] + j >= 0 && dy[k] + i < board.length
                            && dy[k] + i >= 0) {
                        if (capture[0][dy[k] + i][dx[k] + j] == 0) {
                            surround = false;
                        }
                    }
                }
                if (surround) {
                    state = 1;
                }
            } else if (capture[1][king[0][0]][king[0][1]] != 0) {
                int i = king[0][0];
                int j = king[0][1];
                int[] dx = new int[] { 0, 1, 1, 1, 0, -1, -1, -1 };
                int[] dy = new int[] { 1, 1, 0, -1, -1, -1, 0, 1 };
                boolean surround = true;
                for (int k = 0; k < dx.length; k++) {
                    if (dx[k] + j < board[i].length && dx[k] + j >= 0 && dy[k] + i < board.length
                            && dy[k] + i >= 0) {
                        if (capture[1][dy[k] + i][dx[k] + j] == 0) {
                            surround = false;
                        }
                    }
                }
                if (surround) {
                    state = -1;
                }
            }
            if (state == 0) {
                System.out.println("NO CHECKMATE");
            } else if (state == 1) {
                System.out.println("CHECKMATE WHITE");
            } else {
                System.out.println("CHECKMATE BLACK");
            }
        }
        in.close();
        out.close();
    }

    public static void capture(int[][] board, int i, int j, int[][][] capture, int id, int[] dx, int[] dy, int range) {

        for (int k = 0; k < dx.length; k++) {
            int l = 1;
            while (l <= range && dx[k] * l + j < board[i].length && dx[k] * l + j >= 0 && dy[k] * l + i < board.length
                    && dy[k] * l + i >= 0) {
                //if(board[dy[k]*l+i][dx[k]*l+j]!=0)
                        if (board[i][j] == id) {
                    capture[0][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                } else {
                    capture[1][dy[k] * l + i][dx[k] * l + j] = board[i][j];
                }
                l++;
            }
        }
    }
}