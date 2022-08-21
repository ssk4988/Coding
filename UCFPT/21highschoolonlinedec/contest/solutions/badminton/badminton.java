package solutions.badminton;

import java.util.*;

public class badminton {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int numTests = sc.nextInt();
		for(int test = 0; test < numTests; ++test) {
			// use the first character of input to determine who serves
			// to start
			boolean aliceServe = sc.next().charAt(0) == 'A';
			
			int numRounds = sc.nextInt();
			
			// keep track of each score
			int aliceScore = 0, bobScore = 0;
			for(int round = 0; round < numRounds; ++round) {
				// the server will win the point if the number of hits is
				// odd; otherwise, the receiver wins the round
				boolean serverWins = sc.nextInt() % 2 == 1;
				
				if(serverWins) {
					// if the server won the point, add 1 to their score
					if(aliceServe) {
						++aliceScore;
					}
					else {
						++bobScore;
					}
				}
				else {
					// otherwise, the serve changes
					aliceServe = !aliceServe;
				}
			}
			
			// print scores according to format
			System.out.println(aliceScore + "-" + bobScore);
		}
		sc.close();
	}
}