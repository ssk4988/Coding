import java.io.*;
import java.util.*;

public class k2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        char[][][] board = new char[4][10][2];
        board[0][0] = new char[] { 'q', 'Q' };
        board[0][1] = new char[] { 'w', 'W' };
        board[0][2] = new char[] { 'e', 'E' };
        board[0][3] = new char[] { 'r', 'R' };
        board[0][4] = new char[] { 't', 'T' };
        board[0][5] = new char[] { 'y', 'Y' };
        board[0][6] = new char[] { 'u', 'U' };
        board[0][7] = new char[] { 'i', 'I' };
        board[0][8] = new char[] { 'o', 'O' };
        board[0][9] = new char[] { 'p', 'P' };
        board[1][0] = new char[] { 'a', 'A' };
        board[1][1] = new char[] { 's', 'S' };
        board[1][2] = new char[] { 'd', 'D' };
        board[1][3] = new char[] { 'f', 'F' };
        board[1][4] = new char[] { 'g', 'G' };
        board[1][5] = new char[] { 'h', 'H' };
        board[1][6] = new char[] { 'j', 'J' };
        board[1][7] = new char[] { 'k', 'K' };
        board[1][8] = new char[] { 'l', 'L' };
        board[1][9] = new char[] { ';', ':' };
        board[2][0] = new char[] { 'z', 'Z' };
        board[2][1] = new char[] { 'x', 'X' };
        board[2][2] = new char[] { 'c', 'C' };
        board[2][3] = new char[] { 'v', 'V' };
        board[2][4] = new char[] { 'b', 'B' };
        board[2][5] = new char[] { 'n', 'N' };
        board[2][6] = new char[] { 'm', 'M' };
        board[2][7] = new char[] { ',', '<' };
        board[2][8] = new char[] { '.', '>' };
        board[2][9] = new char[] { '/', '?' };
        board[3][0] = new char[] { '^', '^' };
        board[3][1] = new char[] { '^', '^' };
        board[3][2] = new char[] { ' ', ' ' };
        board[3][3] = new char[] { ' ', ' ' };
        board[3][4] = new char[] { ' ', ' ' };
        board[3][5] = new char[] { ' ', ' ' };
        board[3][6] = new char[] { ' ', ' ' };
        board[3][7] = new char[] { ' ', ' ' };
        board[3][8] = new char[] { '^', '^' };
        board[3][9] = new char[] { '^', '^' };
        int[] k = new int[] { 30, 39 };
        int[] dx = new int[] { 1, 1, -1, -1, 2, 2, -2, -2 };
        int[] dy = new int[] { 2, -2, 2, -2, 1, -1, 1, -1 };
        ArrayList<Integer>[][] n = new ArrayList[4][10];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                n[i][j] = new ArrayList<>();
                for (int l = 0; l < dx.length; l++) {
                    if (i + dx[l] >= 0 && i + dx[l] < 4 && j + dy[l] >= 0 && j + dy[l] < 10) {
                        n[i][j].add((i + dx[l]) * 10 + j + dy[l]);
                    }
                }
            }
        }
        String line;
        while (!(line = in.readLine()).equals("*")) {
            boolean works = solve(k, board, n, 0, line);
            System.out.println(works ? 1 : 0);
        }
        in.close();
    }

    public static boolean solve(int[] k, char[][][] board, ArrayList<Integer>[][] n, int depth, String s) {
        if (depth == s.length())
            return true;
        int[][] k2 = new int[k.length][2];
        for (int i = 0; i < k.length; i++) {
            k2[i][0] = k[i] / 10;
            k2[i][1] = k[i] % 10;
        }
        char c = s.charAt(depth);
        int shiftOn = (board[k2[0][0]][k2[0][1]][0] == '^'? 1 : 0 )+ (board[k2[1][0]][k2[1][1]][0] == '^'?1:0);
        boolean shiftNeed = Character.isUpperCase(c) || c == '?' || c == '>' || c == '<' || c == ':';
        if (!shiftNeed && shiftOn==2) {
            return false;
        }
        
        for (int ki = 0; ki < 2; ki++) {
            for (int n1 : n[k2[ki][0]][k2[ki][1]]) {
                int i1 = n1 / 10;
                int j1 = n1 % 10;
                if (!(shiftNeed && shiftOn == 0) && board[i1][j1][board[k2[1-ki][0]][k2[1-ki][1]][0]=='^'?1:0] == c) {
                    int[] nk = new int[2];
                    nk[ki] = n1;
                    nk[1 - ki] = k[1 - ki];
                    if (solve(nk, board, n, depth+1, s))
                        return true;
                }
                else if(board[i1][j1][0] == '^'){
                    int[] nk = new int[2];
                    nk[ki] = n1;
                    nk[1 - ki] = k[1 - ki];
                    if (solve(nk, board, n, depth, s))
                        return true;
                }
            }
        }
        
        /*if (shiftNeed && shiftOn==0) {
            for (int ki = 0; ki < 2; ki++) {
                for (int n1 : n[k2[ki][0]][k2[ki][1]]) {
                    int i1 = n1 / 10;
                    int j1 = n1 % 10;
                    if (board[i1][j1][0] == '^') {
                        int[] nk = new int[2];
                        nk[ki] = n1;
                        nk[1 - ki] = k[1 - ki];
                        if (solve(nk, board, n, depth, s))
                            return true;
                    }
                }
            }
        } else if (!shiftNeed && shiftOn==2) {
            return false;
        } 
        else if(!shiftNeed && shiftOn == 1){
            for (int ki = 0; ki < 2; ki++) {
                if (board[k2[ki][0]][k2[ki][1]][0] != '^')
                    continue;
                for (int n1 : n[k2[ki][0]][k2[ki][1]]) {
                    int i1 = n1 / 10;
                    int j1 = n1 % 10;
                    if (board[i1][j1][0] == c) {
                        int[] nk = new int[2];
                        nk[ki] = n1;
                        nk[1 - ki] = k[1 - ki];
                        if (solve(nk, board, n, depth + 1, s))
                            return true;
                    }
                }
            }
        }
        else {
            // need and on or not need and not on
            for (int ki = 0; ki < 2; ki++) {
                if (shiftNeed && shiftOn==1 && board[k2[ki][0]][k2[ki][1]][0] == '^' && board[k2[1-ki][0]][k2[1-ki][1]][0] != '^')
                    continue;
                for (int n1 : n[k2[ki][0]][k2[ki][1]]) {
                    int i1 = n1 / 10;
                    int j1 = n1 % 10;
                    if (board[i1][j1][shiftOn>0 ? 1 : 0] == c) {
                        int[] nk = new int[2];
                        nk[ki] = n1;
                        nk[1 - ki] = k[1 - ki];
                        if (solve(nk, board, n, depth + 1, s))
                            return true;
                    }
                }
            }
        }*/
        return false;
    }
}