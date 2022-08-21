package solutions.prob7;

// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #7: Downhill Markble Labyrinth

import java.util.*;

public class prob7 {

	final public static int[] DX = { -1, 0, 0, 1 };
	final public static int[] DY = { 0, -1, 1, 0 };

	final public static int MOD = 1000;

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Go through each case.
		for (int loop = 0; loop < numCases; loop++) {

			int r = stdin.nextInt();
			int c = stdin.nextInt();

			// Get the grid.
			int[][] grid = new int[r][c];
			pair[] items = new pair[r * c];
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					grid[i][j] = stdin.nextInt();
					items[i * c + j] = new pair(c * i + j, grid[i][j]);
				}
			}

			// Put in elevation order.
			Arrays.sort(items);

			// Set up array.
			int[][] dp = new int[r][c];

			// Go through each square in order.
			for (int i = 0; i < r * c; i++) {

				// Can't overwrite this!
				if (items[i].spot == 0) {
					dp[0][0] = 1;
					continue;
				}

				// Get cur spot.
				int curX = items[i].spot / c;
				int curY = items[i].spot % c;

				// Add up all contributions from all 4 sides.
				for (int j = 0; j < DX.length; j++) {
					int nextX = curX + DX[j];
					int nextY = curY + DY[j];
					if (nextX < 0 || nextX >= r || nextY < 0 || nextY >= c)
						continue;
					dp[curX][curY] = (dp[curX][curY] + dp[nextX][nextY]) % MOD;
				}
			}

			// This is the result we want.
			System.out.println(dp[r - 1][c - 1]);
		}
		stdin.close();
	}
}

class pair implements Comparable<pair> {

	public int spot;
	public int elevation;

	public pair(int mySpot, int myElevation) {
		spot = mySpot;
		elevation = myElevation;
	}

	public int compareTo(pair other) {
		return other.elevation - this.elevation;
	}
}