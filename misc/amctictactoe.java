/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class amctictactoe {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int[][] board = new int[3][3];
        for (int i = 0; i < 3; i++) {
            Arrays.fill(board[i], -1);
        }
        Tictactoe start = new Tictactoe(board);
        Queue<Tictactoe> queue = new LinkedList<>();
        queue.add(start);
        int numGames = 0;
        int num6 = 0;
        Set<String> end6 = new HashSet<>();
        while (!queue.isEmpty()) {
            Tictactoe next = queue.poll();
            if (next.moves == 6 && next.terminal) {
                end6.add(next.toString());
                num6++;
            }
            numGames++;
            for (Tictactoe c : next.children) {
                queue.add(c);
            }
        }
        System.out.println(numGames);
        System.out.println(end6.size());

        in.close();
        out.close();
    }

    public static class Tictactoe {
        public int[][] board;
        public int moves = 9;
        public boolean terminal = false;
        public ArrayList<Tictactoe> children = new ArrayList<>();

        public Tictactoe(int[][] board) {
            this.board = board;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (this.board[i][j] == -1) {
                        this.moves--;
                    }
                }
            }
            isTerminal();
            getChildren();
        }

        public String toString() {
            return Arrays.toString(board[0]) + Arrays.toString(board[1]) + Arrays.toString(board[2]);
        }

        public ArrayList<Tictactoe> getChildren() {
            if (!terminal) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (this.board[i][j] == -1) {
                            int[][] board2 = new int[3][3];
                            for (int i2 = 0; i2 < 3; i2++) {
                                for (int j2 = 0; j2 < 3; j2++) {
                                    board2[i2][j2] = board[i2][j2];
                                }
                            }
                            board2[i][j] = moves % 2;
                            Tictactoe c = new Tictactoe(board2);
                            children.add(c);
                        }
                    }
                }
            }
            return children;
        }

        public boolean isTerminal() {
            if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != -1) {
                terminal = true;
            }
            if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != -1) {
                terminal = true;
            }
            if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != -1) {
                terminal = true;
            }
            if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != -1) {
                terminal = true;
            }
            if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != -1) {
                terminal = true;
            }
            if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != -1) {
                terminal = true;
            }
            if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != -1) {
                terminal = true;
            }
            if (board[2][0] == board[1][1] && board[0][2] == board[1][1] && board[2][0] != -1) {
                terminal = true;
            }
            return terminal;
        }
    }
}