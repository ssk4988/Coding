package solutions.picky;

import java.util.*;

public class picky_alternative{

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for(int q = 1; q <= t; q++){
            int n = scan.nextInt();
            int m = scan.nextInt();
            Vec[] pts = new Vec[n];
            for(int i = 0; i < n; i++)
                pts[i] = new Vec(scan.nextInt(), scan.nextInt());
            Vec[] topping = new Vec[m];
            for(int i = 0; i < m; i++)
                topping[i] = new Vec(scan.nextInt(), scan.nextInt());

            boolean found = false;
            double ans = Integer.MAX_VALUE;
            // Check between which two vertices we make the cut
            for(int i = 0; i < n; i++){
                LOOP: for(int j = i+2; j < n; j++) {
                    // Because it is guaranteed that each topping lies in the polygon,
                    // we can just check which side of the cut the topping is on
                    int numToppingsA = 0;
                    int numToppingsB = 0;
                    for(int k = 0; k < m; k++){
                        int s = side(pts[i], pts[j], topping[k]);
                        if(s == 0) continue LOOP;
                        if(s < 0) numToppingsA++;
                        else numToppingsB++;
                    }

                    if(numToppingsA != numToppingsB) continue;

                    ArrayList<Vec> meghanCut = new ArrayList<Vec>();
                    ArrayList<Vec> natalieCut = new ArrayList<Vec>();
                    for(int k = i; k <= j; k++) meghanCut.add(pts[k]);
                    for(int k = j; k < n; k++) natalieCut.add(pts[k]);
                    for(int k = 0; k <= i; k++) natalieCut.add(pts[k]);

                    double areaA = area(meghanCut);
                    double areaB = area(natalieCut);

                    found = true;
                    ans = Math.min(ans, Math.abs(areaA-areaB));
                }
            }
            System.out.println(found ? "Yes" : "No");
            if(found) System.out.println(ans);
            System.out.println();
        }
        scan.close();
        
    }

    // compute area of polygon
    static double area(ArrayList<Vec> poly){
        double area = 0.0;
        for(int i = 0; i < poly.size(); i++) {
            Vec a = poly.get(i);
            Vec b = poly.get((i+1) % poly.size());
            area += (b.x - a.x) * (b.y + a.y);
        }
        return Math.abs(area) / 2.0;
    }

    // Which side of the line (a->b) is the point c on (positive or negative) using cross product
    // 0 means the point is on the line
    static int side(Vec a, Vec b, Vec c){
        Vec line = b.sub(a);
        Vec vector = c.sub(a);
        return line.cross(vector);
    }

    static class Vec{

        int x;
        int y;

        public Vec(int x, int y){
            this.x = x;
            this.y = y;
        }

        public Vec sub(Vec v){
            return new Vec(x-v.x, y-v.y);
        }

        public int cross(Vec v){
            return x*v.y-y*v.x;
        }
    }
}
