package solutions.picky;

// picky.java by Jacob Steinebronn
import java.util.*;
public class picky {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int ntest = s.nextInt();
        while(ntest-->0){
            int n = s.nextInt(), m = s.nextInt();
            Vec[] poly, toppings;
            Arrays.setAll(poly = new Vec[n], p->new Vec(s.nextInt(), s.nextInt()));
            Arrays.setAll(toppings = new Vec[m], p->new Vec(s.nextInt(), s.nextInt()));
            double ans = 1e9;

            // Use the shoelace theorem to calculate the area of the entire pizza
            double totalarea = 0;
            for(int i = 0; i < n; i++)
                totalarea += poly[i].cross(poly[(i+1)%n]);
            totalarea = Math.abs(totalarea)/2;

            for(int i = 0; i < n; i++){
                for(int j = i+1; j < n; j++){
                    // For every cut...
                    int topleft = 0;
                    Seg cut = new Seg(poly[i], poly[j]);
                    // For every topping...
                    for(Vec top: toppings){
                        // Check which side of the cut it's on
                        // If the topping is on the cut itself, side will be zero
                        int side = cut.side(top);
                        if(side == -1)topleft++;
                        else if(side == 0){
                            topleft = -1000;
                            break;
                        }
                    }
                    // If we didnt cut a topping in half, and we have an even cut...
                    if(topleft < 0)continue;
                    if(topleft*2 == m){
                        // Use the shoelace theorem to calculate the area of one side of the cut
                        double area = poly[j].cross(poly[i]);
                        for(int k = i; k < j; k++)
                            area += poly[k].cross(poly[(k+1)%n]);
                        area = Math.abs(area)/2;

                        // Check if this cut is more even than the best one yet
                        ans = Math.min(ans, Math.abs(totalarea - 2*area));
                    }
                }
            }

            // We're done!
            if(ans < 1e8){
                System.out.println("Yes\n"+ans+"\n");
            }else{
                System.out.println("No\n");
            }


        }
        s.close();
    }

    // Seg class, stores a line segment
    static class Seg {
        Vec from, to, dir;
        
        public Seg(Vec from, Vec to) {
            this.from=from;
            this.to=to;
            dir=to.sub(from);
        }
        
        //returns 1 if above, 0 if on, -1 if below
        public int side(Vec o) {
            Vec oDir=o.sub(from);
            double distFromLine=dir.unit().cross(oDir);
            if (Vec.eq(distFromLine, 0))
                return 0;
            return (int)Math.signum(distFromLine);
        }
        
    }
    // Vector class with some basic operations
    static class Vec {
        static final double EPS=1e-6;
        double x, y;
        public Vec(double x, double y) {this.x=x;this.y=y;}
        public Vec sub(Vec o) {return new Vec(x-o.x, y-o.y);}
        public Vec scale(double s) {return new Vec(x*s, y*s);}
        public double dot(Vec o) {return x*o.x+y*o.y;}
        public double cross(Vec o) {return x*o.y-y*o.x;}
        public double mag2() {return dot(this);}
        public double mag() {return Math.sqrt(mag2());}
        public Vec unit() {return scale(1/mag());}
        
        static boolean eq(double a, double b) {return Math.abs(a-b)<EPS;}
    }
}
