import java.io.*;
import java.util.*;

public class pasture {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numCows = Integer.parseInt(in.readLine());
        cow[] cows = new cow[numCows];
        cow[] xcows = new cow[numCows];
        cow[] ycows = new cow[numCows];
        cow[] cow2 = new cow[numCows];
        Map<Integer, Integer> xcompress = new HashMap<>();
        Map<Integer, Integer> ycompress = new HashMap<>();
        ArrayList<Integer> xmap = new ArrayList<>();
        ArrayList<Integer> ymap = new ArrayList<>();
        int[] xs = new int[numCows];
        int[] ys = new int[numCows];
        Set<Integer> xset = new TreeSet<>();
        Set<Integer> yset = new TreeSet<>();
        xset.add(-1);
        yset.add(-1);
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            xs[i] = Integer.parseInt(tokenizer.nextToken());
            ys[i] = Integer.parseInt(tokenizer.nextToken());
            xset.add(xs[i]);
            yset.add(ys[i]);
        }
        for (int x : xset) {
            xmap.add(x);
            xcompress.put(x, xcompress.size());
        }
        for (int y : yset) {
            ymap.add(y);
            ycompress.put(y, ycompress.size());
        }
        for (int i = 0; i < numCows; i++) {
            cows[i] = new cow(xcompress.get(xs[i]), ycompress.get(ys[i]), xs[i], ys[i]);
            cow2[i] = xcows[i] = ycows[i] = cows[i];
        }
        Arrays.sort(xcows, new cowX());
        Arrays.sort(ycows, new cowY());
        for (int i = 0; i < xcows.length - 1; i++) {
            xcows[i].right = xcows[i + 1];
        }
        for (int i = 0; i < ycows.length - 1; i++) {
            ycows[i].up = ycows[i + 1];
        }
        int[][] prefix = new int[xcompress.size()][ycompress.size()];
        for (int i = 0; i < numCows; i++) {
            prefix[cows[i].x][cows[i].y]++;
        }

        int answer = 1;// empty
        for (int i = 0; i < cows.length; i++) {
            cow start = cows[i];
            int dist = -1;
            int prevDist = -1;
            cow pointer = cows[i];
            comp c = new comp(start);
            Arrays.sort(cow2, c);
            int j = 0;
            while(c.compare(start, cow2[j]) < 0){
                j++;
            }
            while(j < cow2.length){
                prevDist = dist;
                dist = c.compare(start, cow2[j]);
                if(dist > prevDist){
                    answer++;
                }
                j++;
            }
            /*
            //answer++;
            while (pointer != null) {
                pointer.visited = true;
                prevDist = dist;
                dist = Math.max(prevDist, Math.max(pointer.orrX - start.orrX, pointer.orrY - start.orrY));
                /*if(Math.max(pointer.up == null ? 0 : pointer.up.orrY - start.orrY, pointer.right == null ? 0 : pointer.right.orrX - start.orrX) > dist){
                    if((pointer.up == null ? Integer.MAX_VALUE : pointer.up.orrY - start.orrY) < (pointer.right == null ? Integer.MAX_VALUE : pointer.right.orrX - start.orrX)){
                        pointer = pointer.up;
                        dist = pointer.orrY - start.orrY;
                    }
                    else{
                        pointer = pointer.right;
                        dist = pointer.orrX - start.orrX;
                    }
                }
                else{
                    break;
                }
                if(dist > prevDist){
                    answer++;
                }

                pointer = pointer.right;                
            }*/
            System.out.println(i + " " + answer);
        }
        /*
         * for (int i = 1; i < prefix.length; i++) {
         * for (int j = 1; j < prefix[i].length; i++) {
         * prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
         * }
         * }
         * for (int i = 0; i < prefix.length - 1; i++) {
         * for (int j = 0; j < prefix[i].length - 1; i++) {
         * int startx = i;
         * int starty = j;
         * int currx = i + 1;
         * int curry = j + 1;
         * if (prefix[currx][curry] <= prefix[startx][starty]) {
         * continue;
         * }
         * outer: while (currx < prefix.length && curry < prefix[i].length) {
         * while (prefix[currx][curry] <= prefix[startx][starty]) {
         * if (!(currx + 1 < prefix.length) && !(curry + 1 < prefix[i].length)) {
         * break outer;
         * } else if (!(currx + 1 < prefix.length)) {
         * curry++;
         * } else if (!(curry + 1 < prefix[i].length)) {
         * currx++;
         * } else if (xmap.get(currx + 1) - xmap.get(currx) < ymap.get(curry + 1) -
         * ymap.get(curry)) {
         * currx++;
         * } else if (xmap.get(currx + 1) - xmap.get(currx) > ymap.get(curry + 1) -
         * ymap.get(curry)) {
         * curry++;
         * } else if (xmap.get(currx + 1) - xmap.get(currx) == ymap.get(curry + 1) -
         * ymap.get(curry)) {
         * currx++;
         * curry++;
         * } else {
         * System.out.println("you buggin bruh");
         * }
         * }
         * answer++;
         * }
         * }
         * }
         */
        System.out.println(answer);
        in.close();
    }
    public static class comp implements Comparator<cow> {
        int x;
        int y;
        public comp(cow c){
            this.x = c.orrX;
            this.y = c.orrY;
        }
        @Override
        public int compare(pasture.cow o1, pasture.cow o2) {
            int i1 = 0;
            if(o1.orrX < x || o1.orrY < y){
                i1 = Math.min(o1.orrX - x, o1.orrY - y);
            }
            else{
                i1 = Math.max(o1.orrX - x, o1.orrY - y);
            }
            int i2 = 0;
            if(o2.orrX < x || o2.orrY < y){
                i2 = Math.min(o2.orrX - x, o2.orrY - y);
            }
            else{
                i2 = Math.max(o2.orrX - x, o2.orrY - y);
            }
            return i1 - i2;
        }
    }
    public static class cowX implements Comparator<cow> {
        @Override
        public int compare(pasture.cow o1, pasture.cow o2) {
            return o1.x - o2.x;
        }
    }

    public static class cowY implements Comparator<cow> {
        @Override
        public int compare(pasture.cow o1, pasture.cow o2) {
            return o1.y - o2.y;
        }
    }

    public static class cow {
        int x;
        int y;
        int orrX;
        int orrY;
        cow right = null;
        cow up = null;
        boolean visited = false;

        public cow(int x, int y, int orrX, int orrY) {
            this.x = x;
            this.y = y;
            this.orrX = orrX;
            this.orrY = orrY;
        }
    }
}