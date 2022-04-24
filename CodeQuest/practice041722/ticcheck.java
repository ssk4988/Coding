import java.io.*;
import java.util.*;

public class ticcheck {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            String s= in.readLine();
            int board = 1;
            for (int i = 0; i < 9; i++) {
                if (s.charAt(i) != '-') {
                    board |= 1 << (1 + i);
                    if (s.charAt(i) == 'X') {
                        board |= 1 << (1 + 9 + i);
                    }
                }
            }
            int score = terminal(board);
            b.append(s);
            b.append(" = ");
            if(score == 1){
                b.append("X WINS\n");
            }
            else if(score == -1){
                b.append("O WINS\n");
            }
            else{
                b.append("TIE\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
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