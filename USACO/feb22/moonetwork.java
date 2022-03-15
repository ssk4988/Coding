import java.io.*;
import java.util.*;

public class moonetwork {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        cow[] cows = new cow[n];
        Comparator<cow> sortbyx = new byX();
        Comparator<cow> sortbydist = new byDist();
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
        /*
         * for(int i = 0; i < rows.length; i++){
         * Collections.sort(rows[i], comp);
         * }
         */
        cows[0].dist = 0;
        PriorityQueue<cow> queue = new PriorityQueue<>(sortbydist);
        queue.add(cows[0]);
        int remains = 0;
        for(int i = 0; i < rows.length; i++){
            remains += rows[i].size();
            for(cow c : rows[i].values()){
                //queue.add(c);
            }
        }
        //long cost = 0;
        while (remains > 0 && !queue.isEmpty()) {
            cow c = queue.poll();
            if (c.used)
                continue;
            c.used = true;
            // int index = Collections.binarySearch(rows[c.y], c, comp);
            rows[c.y].remove(c.x);

            remains--;
            //cost += c.dist;
            ArrayList<cow> adds = new ArrayList<>();
            for (int i = 0; i < rows.length; i++) {
                /*
                 * int e = Collections.binarySearch(rows[i], c, comp);
                 * if(e >= 0){
                 * update(queue, c, rows[i].get(e));
                 * }
                 * else{
                 * e = -e - 1;
                 * if(e > 0){
                 * cow l = rows[i].get(e - 1);
                 * update(queue, c, l);
                 * }
                 * if(e + 1 < rows[i].size()){
                 * cow r = rows[i].get(e + 1);
                 * update(queue, c, r);
                 * }
                 * }
                 */
                cow e = rows[i].get(c.x);
                if(e != null){
                    update(c, e);
                    adds.add(e);
                }
                Map.Entry<Integer, cow> re = rows[i].higherEntry(c.x);
                if(re != null){
                    update(c, re.getValue());
                    adds.add(re.getValue());
                }
                Map.Entry<Integer, cow> le = rows[i].lowerEntry(c.x);
                if(le != null){
                    update(c, le.getValue());
                    adds.add(le.getValue());
                }/*
                cow l = rows[i].get();
                cow r = rows[i].higher(c);
                if (l != null){
                    update(c, l);
                    adds.add(l);
                }
                if (r != null){
                    update(c, r);
                    adds.add(r);
                } */
            }
            Collections.sort(adds, sortbydist);
            for (int i = 0; i < adds.size(); i++) {
                //adds.get(i).parent = c;
                if (!adds.get(i).used) {
                    queue.add(adds.get(i));
                    //break;
                }
            }
        }
        long cost = 0;
        for(cow c : cows){
            if(c.parent == null) continue;
            cost += getDist(c, c.parent);
        }
        System.out.println(cost);
        in.close();
    }

    public static void update(cow c, cow c2) {
        if (!c.used)
            return;
        if (c2.used)
            return;
        long dist = getDist(c, c2);
        if(dist < c2.dist){
            c2.dist = dist;
            c2.parent = c;
        }
    }

    public static class byX implements Comparator<cow> {
        @Override
        public int compare(moonetwork.cow o1, moonetwork.cow o2) {
            return o1.x - o2.x;
        }
    }

    public static long getDist(cow c1, cow c2) {
        return ((long) (c1.x) - c2.x) * ((long)c1.x - c2.x) + ((long)c1.y - c2.y) * ((long)c1.y - c2.y);
    }

    public static class byDist implements Comparator<cow> {
        @Override
        public int compare(moonetwork.cow o1, moonetwork.cow o2) {
            if (o1.dist > o2.dist)
                return 1;
            if (o1.dist < o2.dist)
                return -1;
            return 0;
        }
    }

    public static class cow {
        int x;
        int y;
        int id;
        cow parent = null;
        boolean used = false;
        long dist = 20000000000000L;

        public cow(int x, int y, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
        }
    }
}