import java.io.*;
import java.util.*;

public class rut {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int numCows = Integer.parseInt(in.readLine());
        ArrayList<Cow> northboundx = new ArrayList<>();
        ArrayList<Cow> eastboundy = new ArrayList<>();
        int maxNorthX = 0;
        int maxNorthY = 0;
        int maxEastX = 0;
        int maxEastY = 0;
        Map<Integer, Integer> coordX = new HashMap<>();
        Map<Integer, Integer> coordY = new HashMap<>();
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String dirstr = tokenizer.nextToken();
            int dir = dirstr.equals("N") ? 0 : 1;
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            coordX.put(x, i);
            coordY.put(y, i);
            if (dir == 0) {
                northboundx.add(new Cow(i, x, y, dir));
                if (x > maxNorthX)
                    maxNorthX = x;
                if (y > maxNorthY)
                    maxNorthY = y;
            } else {
                eastboundy.add(new Cow(i, x, y, dir));
                if (x > maxEastX)
                    maxEastX = x;
                if (y > maxEastY)
                    maxEastY = y;
            }
        }
        northboundx.sort(new Comp());
        eastboundy.sort(new Comp1());
        for (Cow north : northboundx) {
            for (Cow east : eastboundy) {
                if (!(east.x < north.x && east.y > north.y && east.stopX > north.x && north.stopY > east.y)) {
                    continue;
                }
                if (north.x - east.x > east.y - north.y) {
                    east.stopX = north.x;
                }
                if (north.x - east.x == east.y - north.y) {
                    // grasslost[north.id]++;
                    // grasslost[east.id]++;
                }
                if (north.x - east.x < east.y - north.y) {
                    north.stopY = east.y;
                }
            }
        }
        int[] stopped = new int[numCows];
        Arrays.fill(stopped, -1);
        int[] blame = new int[numCows];
        for (Cow north : northboundx) {
            if (north.stopY == Integer.MAX_VALUE)
                continue;
            stopped[north.id] = coordY.get(north.stopY);
            // System.out.println(coordY.get(north.stopY) + " stopped " + north.id);
        }
        for (Cow east : eastboundy) {
            if (east.stopX == Integer.MAX_VALUE)
                continue;
            stopped[east.id] = coordX.get(east.stopX);
            // System.out.println(coordX.get(east.stopX) + " stopped " + east.id);
        }
        for (int i = 0; i < numCows; i++) {
            int parent = stopped[i];
            while (parent != -1) {
                blame[parent]++;
                parent = stopped[parent];
            }
        }
        for (int i = 0; i < numCows; i++) {
            System.out.println(blame[i]);
        }

        in.close();
        // out.close();
    }

    public static class Cow {
        int id;
        int x;
        int y;
        int dir; // 0 N 1 E
        int stopX = Integer.MAX_VALUE;
        int stopY = Integer.MAX_VALUE;
        int halt = 0; // 0 unknown 1 true 2 false

        public Cow(int id, int x, int y, int dir) {
            this.id = id;
            this.x = x;
            this.y = y;
            this.dir = dir;
            if (dir == 0) {
                this.stopX = x;
            } else {
                this.stopY = y;
            }
        }
    }

    public static class Comp implements Comparator<Cow> {
        @Override
        public int compare(rut.Cow o1, rut.Cow o2) {
            return o1.x - o2.x;
        }
    }

    public static class Comp1 implements Comparator<Cow> {
        @Override
        public int compare(rut.Cow o1, rut.Cow o2) {
            return o1.y - o2.y;
        }
    }

}