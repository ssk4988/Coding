import java.util.*;
import java.io.*;

public class aerospace {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int length = Integer.parseInt(in.readLine());
        
        for (int i = 0; i < length; i ++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<Ship> ships = new ArrayList<>();

            for (int j = 0; j < n; j ++) {
                String input = in.readLine();
                String first = input.split(":")[0];
                String second = input.split(":")[1];
                String name = first.split("_")[0];
                char type = first.split("_")[1].toCharArray()[0];
                int x = Integer.parseInt(second.split(",")[0]);
                int y = Integer.parseInt(second.split(",")[1]);
                ships.add(new Ship(name, type, x, y));
            }

            
            while(ships.size() > 0) {
                Collections.sort(ships);
                Ship removed = ships.remove(0);
                b.append("Destroyed Ship: " + removed.name + " xLoc: " + removed.x + "\n");
                for (Ship a : ships) {
                    a.reduce();
                }
            }
        }

        System.out.print(b);
        in.close();
    }
    public static class Ship implements Comparable<Ship> {
        String name;
        char type;
        int x, y;
        public Ship (String name, char type, int x, int y) {
            this.name = name;
            this.x = x;
            this.y = y;
            this.type = type;
        }
        @Override
        public int compareTo(aerospace.Ship o) {
            if (this.x - o.x == 0) return o.y - this.y;
            return this.x - o.x;
        }

        public void reduce() {
            if (this.type == 'A') {
                x -= 10;
            }
            else if (this.type == 'B') {
                x-= 20;
            }
            else {
                x-= 30;
            }
        }
    }
}   

