/*
  sliceawtgeom.java
  Any Way You Slice It, MCPC 2012 Problem C
  Java solution by Michael Goldwasser
  (with heavy use of java.awt.geom)
*/

import java.util.*;
import java.io.*;
import java.awt.geom.*;     // provides Point2D and Line2D

public class sliceawtgeom {

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("slice.in"));
        int steps = in.nextInt();
        while (steps > 0) {
            ArrayList<Line2D> lines = new ArrayList<Line2D>();
            Point2D last = new Point2D.Double(0,0);
            double angle = 90;

            boolean safe = true;
            for (int n=1; n <= steps; n++) {
                double degrees = in.nextInt();
                double forward = in.nextInt();
                if (safe) {      // otherwise, just flush extraneous input
                    angle += degrees * Math.PI / 180.0;
                    Point2D next = new Point2D.Double(last.getX() + forward * Math.cos(angle),
                                                      last.getY() + forward * Math.sin(angle));
                    Line2D cut = new Line2D.Double(last, next);
                    for (int k=0; k < lines.size() - 1; k++) {
                        // check all but the most recent edge (which shares endpoint)
                        if (cut.intersectsLine(lines.get(k))) {
                            safe = false;
                            System.out.println(n);
                            break;
                        }
                    }
                    lines.add(cut);
                    last = next;
                }
            }

            if (safe)
                System.out.println("SAFE");

            steps = in.nextInt();
        }
    }
}
