// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #6: The Juggler's Fallacy

import java.util.*;

public class prob6 {

	final public static int MAX = 625;

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = Integer.parseInt(stdin.nextLine());

		// Go through each case.
		for (int loop=0; loop<numCases; loop++) {

			// Get this case.
			String times = stdin.nextLine().trim();
			StringTokenizer tok = new StringTokenizer(times);

			// Stores each time a ball lands at this time step.
			// This is the max period squared, which should be longer than any period
			// specified by the upto 25 balls with individual periods of 25 steps or fewer.
			int[] used = new int[MAX+1];

			ArrayList<Integer> seq = new ArrayList<Integer>();
			while (tok.hasMoreTokens())
				seq.add(Integer.parseInt(tok.nextToken()));

			// Go through each one.
			for (int t=0; t<seq.size(); t++) {

				// Skip this - nothing got thrown.
				if (seq.get(t) == 0) continue;

				// Simulate the ball coming back down each time.
				for (int item=t+seq.get(t); item<used.length; item+=seq.size())
					used[item]++;
			}

			// See more than one ball ever lands at the same time, or if one lands
			// when it's not supposed to.
			boolean res = true;
			for (int i=0; i<used.length; i++)
				if (used[i] > 1 || (used[i] > 0 && seq.get(i%seq.size()) == 0))
					res = false;

			// Output result.
			System.out.print(times);
			System.out.print(" - ");
			if (res) System.out.println("can be juggled");
			else     System.out.println("cannot be juggled");

		}
	}
}