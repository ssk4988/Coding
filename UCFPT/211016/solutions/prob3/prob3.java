package solutions.prob3;

// Arup Guha
// 2/21/2015
// Solution to 2015 Mercer Problem #3: Fizzy Buzzy Bears

import java.util.*;

public class prob3 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);

		int loop = 1;
		int low = stdin.nextInt();
		int high = stdin.nextInt();

		// Go through each case.
		while (low <= high) {

			// Header
			System.out.println("Case " + loop + ":");

			// Go through each line.
			for (int i = low; i <= high; i++) {

				// Add in everything for this output to res.
				String res = "";
				if (i % 3 == 0)
					res += "Mercer";
				if (i % 4 == 0)
					res += "Bears";
				if (i % 18 == 0)
					res += "Grrrr";
				if (i % 33 == 0)
					res += "Bite";
				if (res.length() == 0)
					res += i;

				// Output the answer and move on.
				System.out.println(res);
			}

			// After each case.
			System.out.println();

			// Go to next case.
			low = stdin.nextInt();
			high = stdin.nextInt();
			loop++;
		}
		stdin.close();
	}
}