import java.io.*;
import java.util.*;

public class moonetwork {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        cow[] cows = new cow[n];
        TreeMap<Integer, cow>[] rows = new TreeMap[11];
        for (int i = 0; i < rows.length; i++) {
            rows[i] = new TreeMap<>();
        }
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            cows[i] = new cow(x, y, i);
            rows[y].put(cows[i].x, cows[i]);
        }
        ArrayList<edge> edges = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int y = 0; y <= 10; y++) {
                Integer lower = cows[i].y == y ? rows[y].lowerKey(cows[i].x) : rows[y].floorKey(cows[i].x);
                if(lower != null){
                    edge e = new edge(cows[i], rows[y].get(lower));
                    edges.add(e);
                }
            }
        }
        Collections.sort(edges);
        long cost = 0;
        for(edge e : edges){
            if(find(e.c1)!=find(e.c2)){
                e.c2.parent = e.c1;
                cost += e.dist;
            }
        }
        System.out.println(cost);
        in.close();
    }

    public static class edge implements Comparable<edge>{
        cow c1;
        cow c2;
        long dist = Long.MAX_VALUE;

        public edge(cow c1, cow c2) {
            this.c1 = c1;
            this.c2 = c2;
            dist = getDist(c1, c2);
        }
        @Override
        public int compareTo(moonetwork.edge o) {
            if(this.dist < o.dist) return -1;
            if(this.dist == o.dist) return 0;
            return 1;
        }
    }

    public static long getDist(cow c1, cow c2) {
        return ((long) (c1.x) - c2.x) * ((long) c1.x - c2.x) + ((long) c1.y - c2.y) * ((long) c1.y - c2.y);
    }

    public static cow find(cow c) {
        if (c.parent.parent != c.parent) {
            c.parent = find(c.parent);
        }
        return c.parent;
    }

    public static class cow {
        int x;
        int y;
        int id;
        cow parent = this;

        public cow(int x, int y, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
        }
    }
}