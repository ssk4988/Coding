package solutions.prob4;

// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #4: Find Your Easter Bunny Name

import java.util.*;

public class prob4 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);

		String[] first = new String[26];
		String[] last = new String[26];

		// Read in all the code names.
		for (int i = 0; i < 26; i++)
			first[i] = stdin.nextLine().substring(2);
		for (int i = 0; i < 26; i++)
			last[i] = stdin.nextLine().substring(2);

		int numCases = Integer.parseInt(stdin.nextLine());

		// Go through each case.
		for (int loop = 0; loop < numCases; loop++) {

			// Get this case.
			String name = stdin.nextLine();
			StringTokenizer tok = new StringTokenizer(name);
			String origFirst = tok.nextToken();
			String origLast = tok.nextToken();

			// This is what they want - just sub in.
			System.out.println(name + " = " + first[origFirst.charAt(0) - 'A'] + " " + last[origLast.charAt(0) - 'A']);
		}
		stdin.close();
	}
}