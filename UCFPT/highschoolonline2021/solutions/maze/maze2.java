package solutions.maze;

import java.util.*;
import java.io.*;
public class maze2 {
	static final FS sc = new FS();
	static final PrintWriter pw = new PrintWriter(System.out);

	static final int[] dr = {0, -1, 0, 1}, dc = {1, 0, -1, 0};

	static int R, C;
	static char[][] arr;
	static boolean[][] gas;
	public static void main(String[] args) {
		int t = sc.nextInt();
		for(int tt = 1; tt <= t; ++tt) {
			R = sc.nextInt();
			C = sc.nextInt();
			arr = new char[R][C];
			gas = new boolean[R][C];

			int eR = -1, eC = -1;
			for(int i = 0; i < R; ++i) {
				arr[i] = sc.next().toCharArray();
				for(int j = 0; j < C; ++j) {
					if(arr[i][j] == '*') {
						eR = i;
						eC = j;
						arr[i][j] = '9';
					}
					else if(arr[i][j] == 'G') {
						gas[i][j] = true;
						for(int dd = 0; dd < dr.length; ++dd) {
							int nr = i + dr[dd], nc = j + dc[dd];
							if(inBounds(nr, nc)) gas[nr][nc] = true;
						}
					}
				}
			}

			ArrayDeque<Integer> ad = new ArrayDeque<>();
			boolean[][] seen = new boolean[R][C];

			for(int i = 0; i < R; ++i) {
				for(int j = 0; j < C; ++j) {
					if((i == 0 || i == R - 1 || j == 0 || j == C - 1) && !gas[i][j] && arr[i][j] == '1'){
						ad.add(i);
						ad.add(j);
						seen[i][j] = true;
					}
				}
			}

			while(!ad.isEmpty()) {
				int r = ad.poll(), c = ad.poll();

				for(int dd = 0; dd < dr.length; ++dd) {
					int nr = r + dr[dd], nc = c + dc[dd];

					if(!inBounds(nr, nc) || gas[nr][nc] || seen[nr][nc]) continue;

					if('1' <= arr[nr][nc] && arr[nr][nc] <= '9' && abs(arr[r][c] - arr[nr][nc]) <= 1) {
						ad.add(nr);
						ad.add(nc);
						seen[nr][nc] = true;
						continue;
					}

					// we have a special thing
					for(int ddd = 0; ddd < dr.length; ++ddd) {
						int nnr = nr + dr[ddd], nnc = nc + dc[ddd];

						if(!inBounds(nnr, nnc) || gas[nnr][nnc] || seen[nnr][nnc]) continue;

						int upDist = arr[nnr][nnc] - arr[r][c];
						if(arr[nr][nc] == 'E' || (arr[nr][nc] == 'F' && upDist > 0) || (arr[nr][nc] == 'P' && upDist < 0)) {
							ad.add(nnr);
							ad.add(nnc);
							seen[nnr][nnc] = true;
						}
					}
				}
			}

			pw.println(seen[eR][eC] ? "You've got this!" : "Find another way");
		}
		pw.flush();
	}
	static boolean inBounds(int r, int c) {
		return r >= 0 && r < R && c >= 0 && c < C;
	}
	static int abs(int a) {
		return a >= 0 ? a : -a;
	}
	static class FS {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer("");
		String next() {
			while(!st.hasMoreElements()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch(Exception e) {}
			}
			return st.nextToken();
		}
		int nextInt() {
			return Integer.parseInt(next());
		}
		long nextLong() {
			return Long.parseLong(next());
		}
	}
}
/*
2
9 9
955443322
96999999P
979956677
989769999
9*9699977
999799786
9G8F4561E
999392232
999991999
3 3
234
5*6
789

*/
