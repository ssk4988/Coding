package solutions.piano;

import java.util.*;

public class piano {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int numTests = sc.nextInt();
		for(int test = 0; test < numTests; ++test) {
			String piece = sc.next();
			
			// for each piece, it isn't against the
			// rules for Bob to only play the piece
			// using one hand; this strategy also avoids
			// any possible issue of him crossing his
			// hands as he never places one of his hands
			// on the piano in the first place
			
			// Bob is a left-handed man, so he prefers
			// to play pieces with just his left hand
			// :)
			
			// print an L for each character in the
			// piece
			for(int x = 0; x < piece.length(); ++x) {
				System.out.print('L');
			}
			// don't forget the new line at the end
			System.out.println();
		}
		sc.close();
	}
}