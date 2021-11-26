/*
  slice.java
  Any Way You Slice It, MCPC 2012 Problem C
  Java solution by Andy Harrington
  (implementing low-level math)
*/

import java.io.*;
import java.util.*;
import static java.lang.Math.*;

public class slice
{
    static int NMAX = 100;
    // side i+1 of length d[i] goes forward at angle a[i] from (x[i], y[i]).
    static int[] d = new int[NMAX]; 
    static double[] a = new double[NMAX],
                    x = new double[NMAX+1],
                    y = new double[NMAX+1];
    static int N;  // total segments

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("slice.in"));
        N = in.nextInt();
        while (N > 0) {
            double prevAng = PI/2;
            for (int i = 0; i < N; i++) {
                prevAng = a[i] = prevAng + in.nextInt()*PI/180;
                System.err.format("%f (%f, %f)%n", a[i]*180/PI, x[i], y[i]);
                d[i] = in.nextInt();
                x[i+1] = x[i] + d[i]*cos(a[i]);
                y[i+1] = y[i] + d[i]*sin(a[i]);
            }
            System.err.format("(%f, %f)%n", x[N], y[N]); 
            System.out.println(solve());
            N = in.nextInt();
        }
    }
   
    static String solve()
    {
        for (int i=2; i < N; i++)
            if (collide(i))
                return ""+(i+1);
        return "SAFE";
    }
   
    static boolean collide(int i) // true if seg crosses previous segment
    {
        for (int j = 0; j < i-1; j++) {// stop before previous segment
            double uxv = sin(a[j] - a[i]);  // math comments at the end
            if (abs(uxv) < PI/360) // no bad cases, with endpoint at cross pt
                continue;          // so do not worry about parallel lines
            double t = ((x[j]-x[i])*sin(a[j]) - (y[j]-y[i])*cos(a[j]))/uxv,   
                   s = ((x[j]-x[i])*sin(a[i]) - (y[j]-y[i])*cos(a[i]))/uxv;         
            if (0 <= min(s, t) && s <= d[j] && t <= d[i])
                return true;
        }
        return false;
    }
}

/* 
   The basic vector line intersection math is simpler here with the angles and
   lengths already given:
   If p and q are initial segment endpoints and u and v are unit vectors along 
   them, the lines intersect where there are scalars s, t so p +tu = q + sv
   Crossing with v (meaning the scalar z component), we can solve for t:
   t = ((q-p) x v) / (u x v), similarly s = ((p - q) x u)  / (v x u).
   For the intersection points to be on the segments we need 
   0 <= t <= its segment length, and similarly for s.   u and v are just given
   by the cos and sin of the segment's angle. Lengths are in the input.

   Because we are not allowing the edge cases, I ignore if the two segments
   are parallel.  
*/