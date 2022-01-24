import java.io.*;
import java.util.*;

public class m {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        c: for (int casenum = 0; casenum < numcases; casenum++) {
            int val = Integer.parseInt(in.readLine(), 8);
            boolean[] set = new boolean[19];
            for (int i = 0; i < set.length; i++) {
                int bit = (1 << i);
                if ((bit & val) == bit) {
                    set[i] = true;
                }
            }
            for (int b = 0; b < 2; b++) {
                boolean type = b == 0;
                boolean win = false;
                for (int row = 0; row < 3; row++) {
                    boolean w = true;
                    for (int i = 0; i < 3; i++) {
                        if (!set[row * 3 + i] || set[9 + row * 3 + i] != type) {
                            w = false;
                        }
                    }
                    if (w) {
                        win = true;
                    }
                }
                for (int col = 0; col < 3; col++) {
                    boolean w = true;
                    for (int i = 0; i < 3; i++) {
                        if (!set[i * 3 + col] || set[9 + i * 3 + col] != type) {
                            w = false;
                        }
                    }
                    if (w) {
                        win = true;
                    }
                }
                boolean w = true;
                for (int i = 0; i < 3; i++) {
                    if (!set[i * 3 + i] || set[9 + i * 3 + i] != type) {
                        w = false;
                    }
                }
                if (w) {
                    win = true;
                }
                w = true;
                for (int i = 0; i < 3; i++) {
                    if (!set[i * 3 + 2 - i] || set[9 + i * 3 + 2 - i] != type) {
                        w = false;
                    }
                }
                if (w) {
                    win = true;
                }
                if (win) {
                    System.out.println((type ? "X" : "O") + " wins");
                    continue c;
                }
            }
            boolean used = true;
            for (int i = 0; i < 9; i++) {
                if (!set[i]) {
                    used = false;
                }
            }
            if (used) {
                System.out.println("Cat\'s");
                continue c;
            }
            System.out.println("In progress");
        }
        in.close();
        out.close();
    }
}