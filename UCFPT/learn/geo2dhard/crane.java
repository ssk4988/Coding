// I've literally rewritten this code in C++ and had it not work so I'm just done with this problem



// Arup Guha
// 7/2/2014
// Solution to 2014 World Finals Problem C: Crane Balancing

import java.util.*;

public class crane {

    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);
        int n = stdin.nextInt();

        int[] x = new int[n+1];
        int[] y = new int[n+1];
        double area = 0, cx = 0, cy = 0;
        int minX=0, maxX=0;
        boolean assigned = false;
        
        // Read in the points storing the first point last for our
        // centroid calculation.
        for (int i=0; i<n+1; i++) {

            if (i < n) {
                x[i] = stdin.nextInt();
                y[i] = stdin.nextInt();
            }
            else {
                x[i] = x[0];
                y[i] = y[0];
            }

			// Find the starting point.
            if (y[i] == 0) {
                if (!assigned) {
                    minX = x[i];
                    maxX = x[i];
                    assigned = true;
                }
                else if (x[i] < minX) minX = x[i];
                else if (x[i] > maxX) maxX = x[i];
            }

			// Do the centroid calculation.
            if (i > 0) {
                double cross = x[i-1]*y[i] - x[i]*y[i-1];
                area += cross;
                cx += (x[i-1]+x[i])*cross;
                cy += (y[i-1]+y[i])*cross;
            }
        }

        // Fix up these values.
        area /= 2;
        cx /= (6*area);
        cy /= (6*area);
        area = Math.abs(area);

        // Lots of cases here.

		// Knock out easy unstable cases.
        if (cx < minX-1e-9 && x[0] <= minX) System.out.println("unstable");
        else if (cx > maxX+1e-9 && x[0] >= maxX) System.out.println("unstable");
        
        // Always works.
        else if (x[0] >= minX && x[0] <= maxX && cx >= minX-1e-9 && cx <= maxX+1e-9) System.out.println("0 .. inf");
        
        // This is the fun part.
        else {

			// Centroid x is within the base.
            if (cx >= minX-1e-9 && cx <= maxX+1e-9) {

				// Hanging point off to the right.
                if (x[0] > maxX) {
                    long w = (long)((maxX - cx)/(x[0] - maxX)*area + 1 - 1e-9);
                    if (w > 0) System.out.println("0 .. "+w);
                    else       System.out.println("unstable");
                }
                
                // Hanging point not off the right.
                else {

                    long w = (long)( (cx - minX)/(minX - x[0])*area + 1 - 1e-9);
                    if (w > 0) System.out.println("0 .. "+w);
                    else       System.out.println("unstable");
                }
            }

			// Centroid x is to the left.
            else if (cx < minX-1e-9) {

				// Hanging poing off the right.
                if (x[0] > maxX) {

                    long loww = (long)((minX - cx)/(x[0]-minX)*area +1e-9);
                    long highw = (long)( (maxX - cx)/(x[0] - maxX)*area + 1 - 1e-9);
                    System.out.println(loww+" .. "+highw);
                }

				// Hanging point not off the right.
                else {
                    long w = (long)((minX - cx)/(x[0]-minX)*area +1e-9);
                    System.out.println(w+" .. inf");
                }

            }

			// Centroid x is to the right.
            else {

				// Hanging point to the left.
                if (x[0] < minX) {
                    long loww = (long)((cx - maxX)/(maxX-x[0])*area +1e-9);
                    long highw = (long)((cx - minX)/(minX - x[0])*area  + 1 - 1e-9);
                    System.out.println(loww+" .. "+highw);
                }

				// Not to the left.
                else {
                    long w = (long)((cx - maxX)/(maxX-x[0])*area +1e-9);
                    System.out.println(w+" .. inf");
                }

            }
        }
    }
}
