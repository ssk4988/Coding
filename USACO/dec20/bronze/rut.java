import java.io.*;
import java.util.*;

public class rut {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //PrintWriter out = new PrintWriter(System.out);
        int numCows = Integer.parseInt(in.readLine());
        ArrayList<Cow> northboundx = new ArrayList<>();
        ArrayList<Cow> eastboundy = new ArrayList<>();
        int maxNorthX = 0;
        int maxNorthY = 0;
        int maxEastX = 0;
        int maxEastY = 0;
        for(int i = 0; i < numCows; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String dirstr = tokenizer.nextToken();
            int dir = dirstr.equals("N") ? 0 : 1;
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            if(dir == 0){
                northboundx.add(new Cow(i, x, y, dir));
                if(x > maxNorthX) maxNorthX = x;
                if(y > maxNorthY) maxNorthY = y;
            }else{
                eastboundy.add(new Cow(i, x, y, dir));
                if(x > maxEastX) maxEastX = x;
                if(y > maxEastY) maxEastY = y;
            }
        }
        northboundx.sort(new Comp());
        eastboundy.sort(new Comp1());
        int[] grasslost = new int[numCows];
        for(Cow north : northboundx){
            for(Cow east : eastboundy){
                if(!(east.x < north.x && east.y > north.y && east.stopX > north.x && north.stopY > east.y)){
                    continue;
                }
                if(north.x - east.x > east.y - north.y){
                    east.stopX = north.x;
                }
                if(north.x - east.x == east.y - north.y){
                    //grasslost[north.id]++;
                    //grasslost[east.id]++;
                }
                if(north.x - east.x < east.y - north.y){
                    north.stopY = east.y;
                }
            }
        }
        int[] grassarr = new int[numCows];
        for(Cow north : northboundx){
            int grass = north.stopY == Integer.MAX_VALUE ? north.stopY : north.stopY - north.y - grasslost[north.id];
            //System.out.println(north.id + " " + grass + " " + north.x + " " + north.y + " " + north.stopY);
            grassarr[north.id] = grass;
        }
        for(Cow east : eastboundy){
            int grass = east.stopX == Integer.MAX_VALUE ? east.stopX : east.stopX - east.x - grasslost[east.id];
            //System.out.println(east.id + " " + grass + " " + east.x + " " + east.y + " " + east.stopX);
            grassarr[east.id] = grass;
        }
        for(int i = 0; i < numCows; i++){
            if(grassarr[i] == Integer.MAX_VALUE){
                System.out.println("Infinity");
            }
            else{
                System.out.println(grassarr[i]);
            }
        }

        in.close();
        //out.close();
    }
    public static class Cow{
        int id;
        int x;
        int y;
        int dir; //0 N 1 E
        int stopX = Integer.MAX_VALUE;
        int stopY = Integer.MAX_VALUE;
        int halt = 0; //0 unknown 1 true 2 false
        public Cow(int id, int x, int y, int dir){
            this.id = id;
            this.x = x;
            this.y = y;
            this.dir = dir;
            if(dir == 0){
                this.stopX = x;
            }
            else{
                this.stopY = y;
            }
        }
    }
    public static class Comp implements Comparator<Cow>{
        @Override
        public int compare(rut.Cow o1, rut.Cow o2) {
            return o1.x - o2.x;
        }
    }
    public static class Comp1 implements Comparator<Cow>{
        @Override
        public int compare(rut.Cow o1, rut.Cow o2) {
            return o1.y - o2.y;
        }
    }

}