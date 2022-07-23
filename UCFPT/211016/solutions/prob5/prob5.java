package solutions.prob5;

// Arup Guha
// 1/19/2015
// Solution for 2015 Mercer Programming Contest Problem #5: Triathlon

import java.util.*;

public class prob5 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Go through each case.
		for (int loop = 1; loop <= numCases; loop++) {

			// Read data for this race.
			int n = stdin.nextInt();
			int swim = stdin.nextInt();
			int bike = stdin.nextInt();
			int run = stdin.nextInt();

			// Read in each racer.
			athlete[] racers = new athlete[n];
			for (int i = 0; i < n; i++) {
				String name = stdin.next();
				double swimSpeed = stdin.nextDouble();
				double bikeSpeed = stdin.nextDouble();
				double runSpeed = stdin.nextDouble();
				racers[i] = new athlete(name, swimSpeed, bikeSpeed, runSpeed);
				racers[i].setSeconds(swim, bike, run);
			}

			// Sort them.
			Arrays.sort(racers);

			// Print them.
			System.out.println("Triathlon #" + loop);
			for (int i = 0; i < n; i++)
				System.out.println(racers[i].display());
		}
		stdin.close();
	}
}

class athlete implements Comparable<athlete> {

	public String name;
	public double swimSpeed;
	public double bikeSpeed;
	public double runSpeed;
	public double seconds;

	// Typical constructor.
	public athlete(String n, double swim, double bike, double run) {
		name = n;
		swimSpeed = swim;
		bikeSpeed = bike;
		runSpeed = run;
	}

	// Just add up the times and use distance = rate x time.
	public void setSeconds(int swimLength, int bikeLength, int runLength) {
		seconds = swimLength / swimSpeed + bikeLength / bikeSpeed + runLength / runSpeed;

		// Check to make sure spec is followed - fractional part must be greater than
		// .01.
		if (seconds - (int) seconds <= .01)
			System.out.println("ERROR - too close to second boundary!!!");
	}

	// We can get away with this since no two competitors will have the same time
	// when their
	// race times in seconds are truncated.
	public int compareTo(athlete other) {

		// Check to make sure spec is followed - no identical finish times when rounded.
		if (((int) this.seconds) - ((int) other.seconds) == 0)
			System.out.println("ERROR - two racers round to same time.");

		return ((int) this.seconds) - ((int) other.seconds);
	}

	// Returns a string storing the line to be displayed for this competitor.
	public String display() {
		int wholeSeconds = (int) seconds;
		int sec = wholeSeconds % 60;
		wholeSeconds /= 60;
		int min = wholeSeconds % 60;
		int hr = wholeSeconds / 60;
		return name + " " + hr + " hour(s) " + min + " minute(s) " + sec + " second(s)";
	}
}
