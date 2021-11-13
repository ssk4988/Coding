// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #2: Snowpocalypse

import java.util.*;

public class prob2 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Go through each case.
		for (int loop=0; loop<numCases; loop++) {

			// Read input.
			int inches = stdin.nextInt();

			// Output result, using int div and mod, as stated in the problem.
			System.out.println((inches/12)+" feet, "+(inches%12)+" inches of snow is the equivalent of "+(inches/10)+" inches of rain");
		}
	}
}
