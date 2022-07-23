package solutions.emoji;

import java.util.Scanner;
import java.util.HashSet;

public class emoji {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();

		testCase: for (int i = 0; i < n; i++) {
			String input = scan.next();

			// Using a HashSet because checking if an element already exists is on average a single
			// operation.
			HashSet<Character> addedLetters = new HashSet<>();

			for (char c : input.toCharArray()) {
				// Check if the character's been added already, and if it has, print out "Nope" and
				// move on to the next test case.
				if (addedLetters.contains(c)) {
					System.out.println("Nope");
					continue testCase;
				}
				addedLetters.add(c);
			}

			// If the program gets to this point, every character is unique.
			System.out.println("Emote away!");
		}
		scan.close();
	}

}
