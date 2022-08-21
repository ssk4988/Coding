package solutions.prob11;

// Arup Guha
// 2/22/2015
// Solution to 2015 Mercer Programming Contest Problem 11: Elliptical Reflections

import java.util.*;

public class prob11 {

	public static void main(String[] args) {

		Scanner stdin = new Scanner(System.in);

		while (true) {

			double[] coords = new double[6];
			for (int i = 0; i < 6; i++)
				coords[i] = stdin.nextDouble();

			if (zero(coords))
				break;

			// Create pts.
			pt focus1 = new pt(coords[0], coords[1]);
			pt onCurve = new pt(coords[2], coords[3]);
			pt focus2 = new pt(coords[4], coords[5]);
			pt center = focus1.midpoint(focus2);

			// Ellipse parameters.
			double a = (focus1.dist(onCurve) + focus2.dist(onCurve)) / 2.0;
			double c = focus1.dist(focus2) / 2.0;
			double b = Math.sqrt(a * a - c * c);

			// Line to intersect with ellipse.
			line pq = new line(onCurve, focus2);

			// Get the result - need to determine major axis.
			pt res = null;
			if (focus1.horizontal(focus2))
				res = intersect(pq, center, a, b);
			else
				res = intersect(pq, center, b, a);

			// Output the result.
			System.out.printf("%.4f %.4f\n", res.x, res.y);
		}
		stdin.close();
	}

	public static pt intersect(line pq, pt center, double a, double b) {

		// Quadratic equation to solve for the parameter on the line for the
		// intersection.
		double sqCoeff = (pq.delta.x * pq.delta.x) / (a * a) + (pq.delta.y * pq.delta.y) / (b * b);
		double xCoeff = 2 * (pq.start.x - center.x) * pq.delta.x / (a * a)
				+ 2 * (pq.start.y - center.y) * pq.delta.y / (b * b);
		double cCoeff = Math.pow(pq.start.x - center.x, 2) / (a * a) + Math.pow(pq.start.y - center.y, 2) / (b * b) - 1;

		// Solve quadratic
		double disc = xCoeff * xCoeff - 4 * sqCoeff * cCoeff;
		double r1 = (-xCoeff + Math.sqrt(disc)) / (2 * sqCoeff);
		double r2 = (-xCoeff - Math.sqrt(disc)) / (2 * sqCoeff);

		// Return the point.
		if (Math.abs(r1) > 1e-9)
			return pq.getPt(r1);
		return pq.getPt(r2);
	}

	public static boolean zero(double[] coords) {
		for (int i = 0; i < coords.length; i++)
			if (Math.abs(coords[i]) > 1e-9)
				return false;
		return true;
	}
}

class pt {

	public double x;
	public double y;

	public pt(double myx, double myy) {
		x = myx;
		y = myy;
	}

	public pt midpoint(pt other) {
		return new pt((this.x + other.x) / 2, (this.y + other.y) / 2);
	}

	public double dist(pt other) {
		return Math.sqrt((this.x - other.x) * (this.x - other.x) + (this.y - other.y) * (this.y - other.y));
	}

	public boolean horizontal(pt other) {
		return Math.abs(this.y - other.y) < 1e-9;
	}
}

class line {

	public pt start;
	public pt end;
	public pt delta;

	public line(pt a, pt b) {
		start = a;
		end = b;
		delta = new pt(end.x - start.x, end.y - start.y);
	}

	public pt getPt(double lambda) {
		return new pt(start.x + delta.x * lambda, start.y + delta.y * lambda);
	}

}