// Arup Guha
// 2/23/2015
// Solution to 2015 Mercer Programming Contest Problem 15: Planet Surveying

import java.util.*;

public class prob15 {

	final public static int STEPS = 10000;
	final public static double STEPANGLE = Math.PI/STEPS;

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);
		int numCases = stdin.nextInt();

		// Process each case.
		for (int loop=0; loop<numCases; loop++) {

			// Get input for case.
			double r = stdin.nextDouble();
			double k = stdin.nextDouble();
			double slope = 1.0/k;

			// Set up approximation.
			double ans = 0, latitude = -Math.PI/2, longitude = 0;
			pt3D cur = new pt3D(0,0,-1);
			for (int i=0; i<STEPS; i++) {

				// Update location.
				latitude += STEPANGLE;
				longitude += (STEPANGLE*slope);
				pt3D next = new pt3D(latitude, longitude);

				// Add distance.
				ans += cur.dist(next);

				// Update point for next iteration.
				cur = next;
			}

			// Output result for sphere with radius r.
			System.out.printf("%.3f\n", r*ans);
		}
	}
}

class pt3D {

	public double x;
	public double y;
	public double z;

	public pt3D(double myx, double myy, double myz) {
		x = myx;
		y = myy;
		z = myz;
	}

	// Creates pt on unit sphere with the given latitude and longitude.
	public pt3D(double latitude, double longitude) {
		z = Math.sin(latitude);
		double tmpRadius = Math.sqrt(1-z*z);
		x = tmpRadius*Math.cos(longitude);
		y = tmpRadius*Math.sin(longitude);
	}

	// Returns the great arc distance between this and other on a unit sphere.
	public double dist(pt3D other) {
		return Math.acos(x*other.x + y*other.y + z*other.z);
	}
}