import java.io.*;
import java.util.*;

public class gridpaths {
    static int cnt = 0;
    static int[] dr = { 1, 0, -1, 0 };
    static int[] dc = { 0, 1, 0, -1 };
    static int[] dir;
    static boolean[][] used = new boolean[9][9];

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s = in.readLine();
        long start = System.currentTimeMillis();
        dir = new int[48];
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '?') {
                dir[i] = -1;
            } else if (s.charAt(i) == 'D') {
                dir[i] = 0;
            } else if (s.charAt(i) == 'R') {
                dir[i] = 1;
            } else if (s.charAt(i) == 'U') {
                dir[i] = 2;
            } else {
                dir[i] = 3;
            }
        }
        for (int k = 0; k < 9; k++) {
            used[0][k] = true;
            used[8][k] = true;
            used[k][0] = true;
            used[k][8] = true;
        }
        solve(0, 1, 1, -1);
        System.out.println(cnt);
        in.close();
        // System.out.println(System.currentTimeMillis() - start);
    }

    public static void solve(int depth, int row, int col, int prevDir) {
        if (row == 7 && col == 1) {
            if (depth == 48)
                cnt++;
            return;
        }
        if (prevDir != -1 && used[row + dr[prevDir]][col + dc[prevDir]]) {
            int rdir = (4 + prevDir + 1) % 4;
            int ldir = (4 + prevDir - 1) % 4;
            if (!used[row + dr[rdir]][col + dc[rdir]] && !used[row + dr[ldir]][col + dc[ldir]]) {
                return;
            }
        }
        used[row][col] = true;
        if (dir[depth] != -1) {
            if (!used[row + dr[dir[depth]]][col + dc[dir[depth]]]) {
                solve(depth + 1, row + dr[dir[depth]], col + dc[dir[depth]], dir[depth]);
            }
        } 
        else if ((col > 2) && used[row][col - 2]
			&& (used[row - 1][col - 1] || used[row + 1][col - 1])
			&& (!used[row][col - 1])) { 
			solve(depth+1, row, col-1, 3);
		}
		else if ((col < 6) && used[row][col + 2]
			&& (used[row - 1][col + 1] || used[row + 1][col + 1] )
			&& (!used[row][col + 1])) {  
            solve(depth+1, row, col+1, 1);
		}
		else if ((row > 2) && used[row - 2][col] 
			&& used[row - 1][col - 1] && (!used[row - 1][col])) {  
            solve(depth+1, row-1, col, 2);
		}
        else {
            for (int k = 0; k < dr.length; k++) {
                if (!used[row + dr[k]][col + dc[k]]) {
                    solve(depth + 1, row + dr[k], col + dc[k], k);
                }
            }
        }
        used[row][col] = false;
    }
}