import java.io.*;
import java.util.*;

public class tictactoe {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            //0000000000000000000
            //00001101 << 4 = 11010000
            //11011001 >> 4 = 00001101
            // 11001 | 01101 = 11101
            int board = 1;
            for (int i = 0; i < 3; i++) {
                String s = in.readLine();
                for (int j = 0; j < 3; j++) {
                    if (s.charAt(j) != '*') {
                        board |= 1 << (1 + j + (i) * 3);
                        if (s.charAt(j) == 'X') {
                            board |= 1 << (1 + 9 + j + (i) * 3);
                        }
                    }
                }
            }
            // System.out.println(board);
            // System.out.println(terminal(board));
            int[] arr = solve(board, 0);
            // System.out.println(terminal(board));
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if ((arr[1] & 1 << (1 + j + (i) * 3)) > 0) {
                        if ((arr[1] & 1 << (1 + 9 + j + (i) * 3)) > 0) {
                            b.append('X');
                        } else {
                            b.append('O');
                        }
                    } else {
                        b.append('*');
                    }
                }
                b.append("\n");
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static int[] solve(int board, int depth) {
        int[] arr = new int[2];
        arr[0] = -5;
        arr[1] = board;
        int t = terminal(board);
        if (t != 0) {
            arr[0] = -1;

            return arr;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ((board & 1 << (1 + j + (i) * 3)) == 0) {
                    int board2 = board;
                    board2 ^= 1;
                    board2 |= 1 << (1 + j + (i) * 3);
                    board2 |= (board & 1) << (1 + 9 + j + (i) * 3); //bruh
                    int[] arr2 = solve(board2, depth + 1);
                    arr2[0] = -arr2[0];
                    if (arr2[0] > arr[0]) {
                        arr[0] = arr2[0];
                        arr[1] = board2;
                    }
                    if (depth == 0) {
                        //System.out.println(i + " " + j + " " + arr2[0]);
                    }
                }
            }
        }
        if (arr[0] == -5) {
            arr[0] = 0;
        }

        return arr;
    }

    public static int terminal(int board) {
        // row
        for (int i = 0; i < 3; i++) {
            int cnt = 0;
            for (int j = 0; j < 3; j++) {
                if ((board & 1 << (1 + j + (i) * 3)) > 0) {
                    if ((board & 1 << (1 + 9 + j + (i) * 3)) > 0) {
                        cnt++;
                    } else {
                        cnt--;
                    }
                }
            }
            // System.out.println(cnt);
            if (Math.abs(cnt) == 3)
                return cnt / 3;
        }
        // col
        for (int j = 0; j < 3; j++) {
            int cnt = 0;
            for (int i = 0; i < 3; i++) {
                if ((board & 1 << (1 + j + (i) * 3)) > 0) {
                    if ((board & 1 << (1 + 9 + j + (i) * 3)) > 0) {
                        cnt++;
                    } else {
                        cnt--;
                    }
                }
            }
            if (Math.abs(cnt) == 3)
                return cnt / 3;
        }
        int cnt = 0;
        // diag 1
        for (int i = 0; i < 3; i++) {

            if ((board & 1 << (1 + i + (i) * 3)) > 0) {
                if ((board & 1 << (1 + 9 + i + (i) * 3)) > 0) {
                    cnt++;
                } else {
                    cnt--;
                }
            }
            // System.out.println(cnt);

        }
        if (Math.abs(cnt) == 3)
            return cnt / 3;
        // diag 2
        cnt = 0;
        for (int i = 0; i < 3; i++) {

            if ((board & 1 << (1 + i + (2 - i) * 3)) > 0) {
                if ((board & 1 << (1 + 9 + i + (2 - i) * 3)) > 0) {
                    cnt++;
                } else {
                    cnt--;
                }
            }
            // System.out.println(cnt);

        }
        if (Math.abs(cnt) == 3)
            return cnt / 3;
        return 0;
    }
}