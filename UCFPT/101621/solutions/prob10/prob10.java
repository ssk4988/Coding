// Arup Guha
// 1/19/2015
// Solution to Mercer 2015 Contest Problem #10: Sum of Squares

import java.util.*;

public class prob10 {

	public static int MAXK = 10000;
	public static int MAXSQ = 100;

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);

		// dp[k][sq] will store the number of solutions that add up to k with the largest square
		// less than or equal to sq^2.
		int[][] dp = new int[MAXK+1][MAXSQ+1];

		// Put in simple solutions into the table.
		Arrays.fill(dp[0], 1);
		Arrays.fill(dp[1], 1);
		dp[1][0] = 0;

		// Loop through all squares.
		for (int k=2; k<=MAXK; k++) {
			for (int sq=2; sq<=MAXSQ; sq++) {

				// Copy over all "old" solutions.
				dp[k][sq] = dp[k][sq-1];

				// Add new ones using sq^2.
				if (sq-2 >= 0 && k-sq*sq >=0) dp[k][sq] += dp[k-sq*sq][sq-2];
			}
		}

		// Process all cases.
		int numCases = stdin.nextInt();
		for (int loop=0; loop<numCases; loop++)
			System.out.println(dp[stdin.nextInt()][MAXSQ]);
	}
}