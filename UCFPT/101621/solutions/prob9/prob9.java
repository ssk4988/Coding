// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #9: Tree Planting

import java.util.*;

public class prob9 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Go through each case.
		for (int loop=0; loop<numCases; loop++) {

			// Read in each case.
			int rows = stdin.nextInt();
			int trees = stdin.nextInt();
			double[] dist = new double[rows];
			double max = 0;
			for (int i=0; i<rows; i++) {
				dist[i] = stdin.nextDouble();
				max = Math.max(max, dist[i]);
			}

			// Output result.
			System.out.printf("%.3f\n",binSearch(trees, max/2, dist));
		}
	}

	public static double binSearch(int trees, double max, double[] dist) {

		// Save initial boundaries.
		double low = 0, high = max;

		while ((high-low) > 1e-8) {

			// This is the value we try.
			double mid = (low+high)/2;

			// Try it!
			boolean canDo = solve(trees, mid, dist);

			// Rest either low or high based mid result.
			if (canDo) low = mid;
			else       high = mid;
		}

		// Should be good enough...
		return low;
	}

	// Just put as many on each row as you can with spacing difference.
	public static boolean solve(int trees, double difference, double[] dist) {
		int ans = 0;
		for (int i=0; i<dist.length; i++)
			ans += Math.max(0, ((int)(dist[i]/difference) - 1));
		return ans >= trees;
	}
}