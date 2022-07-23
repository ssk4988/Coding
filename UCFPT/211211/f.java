import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numcases; casenum++){
            int nwheels = Integer.parseInt(in.readLine());
            wheel[] wheels = new wheel[nwheels];
            for(int i = 0; i < nwheels; i++){
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                int x = Integer.parseInt(tokenizer.nextToken());
                int y = Integer.parseInt(tokenizer.nextToken());
                int radius = Integer.parseInt(tokenizer.nextToken());
                wheels[i] = new wheel(x, y, radius);
                for(int j = 0; j < i; j++){
                    if(Math.pow(wheels[i].radius + wheels[j].radius, 2) == Math.pow(wheels[i].x - wheels[j].x, 2) + Math.pow(wheels[i].y - wheels[j].y, 2)){
                        wheels[i].neighbors.add(wheels[j]);
                        wheels[j].neighbors.add(wheels[i]);
                    }
                }
            }
            wheels[0].solved = true;
            Queue<wheel> q=  new ArrayDeque<>();
            q.add(wheels[0]);
            while(!q.isEmpty()){
                wheel w= q.poll();
                for(wheel x : w.neighbors){
                    if(x.solved) continue;
                    w.rotate(x);
                    x.solved = true;
                    q.add(x);
                }
            }
            for(int i = 0; i < wheels.length; i++){
                if(wheels[i].solved){
                    reduce(wheels[i].speed);out.append(wheels[i].speed[0]);
                    if(wheels[i].speed[1] != 1){
                        out.append("/" + wheels[i].speed[1]);
                    }
                    else{
                    }
                    out.append(" " + (wheels[i].clockwise ? "":"counter") + "clockwise\n");
                }
                else{
                    out.append("not moving\n");
                }
            }
        }
        System.out.print(out);
        in.close();
    }
    public static long gcd(long a, long b){
        if(b == 0) return a;
        if(a < b){
            long tmp = a;
            a = b;
            b = tmp;
        }
        return gcd(b, a % b);
    }
    public static void reduce(long[] o){
        long gcd = gcd(o[0], o[1]);
        o[0] /= gcd;
        o[1] /= gcd;
    }
    public static class wheel{
        long x = 0;
        long y = 0;
        long[] speed = {1, 1};
        boolean solved = false;
        boolean clockwise = true;
        long radius = 0;
        ArrayList<wheel> neighbors = new ArrayList<>();
        public wheel(int x, int y, int radius){
            this.x = x;
            this.y = y;
            this.radius = radius;
        }
        public void rotate(wheel w){
            w.clockwise = !clockwise;
            for(int i = 0; i < 2; i++){
                w.speed[i] = speed[i];
            }
            w.speed[0] *= radius;
            w.speed[1] *= w.radius;
            reduce(w.speed);
        }
    }
}