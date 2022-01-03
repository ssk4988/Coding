import java.io.*;
import java.util.*;

public class close {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numPatches = Integer.parseInt(tokenizer.nextToken());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int john = Integer.parseInt(tokenizer.nextToken());
        grass[] patches = new grass[numPatches];
        for (int i = 0; i < numPatches; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int loc = Integer.parseInt(tokenizer.nextToken());
            int val = Integer.parseInt(tokenizer.nextToken());
            patches[i] = new grass(loc, val);
        }
        Arrays.sort(patches);
        ArrayList<range> ranges = new ArrayList<>();
        int[] cows = new int[numCows + 2];
        for (int i = 0; i < numCows; i++) {
            cows[i] = Integer.parseInt(in.readLine());
        }
        cows[numCows] = -1;
        cows[numCows + 1] = Integer.MAX_VALUE;
        Arrays.sort(cows);
        int point = 0;
        ArrayList<Long> vals = new ArrayList<>();
        for (int i = 1; i < cows.length; i++) {
            ranges.add(new range(cows[i - 1], cows[i]));
            range r = ranges.get(ranges.size() - 1);
            while (point < patches.length && patches[point].loc < cows[i]) {
                r.patches.add(patches[point]);
                patches[point].dist = Math.min(Math.abs((long) patches[point].loc - r.cow1),
                        Math.abs((long) patches[point].loc - r.cow2));
                patches[point].start = patches[point].loc - patches[point].dist;
                patches[point].end = patches[point].loc + patches[point].dist;
                point++;
            }
            while (point < patches.length && patches[point].loc == cows[i]) {
                point++;
            }
            r.calc();
            vals.add(r.val1);
            vals.add(r.val2);
        }
        Collections.sort(vals);
        long answer = 0;
        int i = vals.size() - 1;
        while (i > 0 && john > 0) {
            answer += vals.get(i);
            i--;
            john--;
        }
        System.out.println(answer);
        in.close();
    }

    public static class range {
        int cow1;
        int cow2;
        ArrayList<grass> patches = new ArrayList<>();
        long val1 = 0;
        long val2 = 0;

        public range(int cow1, int cow2) {
            this.cow1 = cow1;
            this.cow2 = cow2;
        }

        public void calc() {
            for (grass g : patches) {
                val2 += g.val;
            }
            if (cow1 == -1 || cow2 == Integer.MAX_VALUE || patches.size() <= 1) {
                val1 = val2;
                val2 = 0;
                return;
            }
            ArrayList<bruh> b = new ArrayList<>();
            for (grass g : patches) {
                b.add(new bruh(false, g.start, g.val));
                b.add(new bruh(true, g.end, g.val));
            }
            Collections.sort(b);
            int point = 0;
            long val = 0;
            while (point < b.size()) {
                long curr = b.get(point).loc;
                long add = 0;
                long sub = 0;
                while (point < b.size() && b.get(point).loc == curr) {
                    if (b.get(point).type) {
                        sub += b.get(point).val;
                    } else {
                        add += b.get(point).val;
                    }
                    point++;
                }
                val1 = Math.max(val1, val);
                val -= sub;
                val1 = Math.max(val1, val);
                val += add;
                val1 = Math.max(val1, val);
            }
            val2 -= val1;
        }
    }

    public static class bruh implements Comparable<bruh> {
        boolean type;
        long loc;
        long val;

        public bruh(boolean type, long loc, long val) {
            this.type = type;
            this.loc = loc;
            this.val = val;
        }

        @Override
        public int compareTo(close.bruh o) {
            if (this.loc < o.loc)
                return -1;
            if (this.loc > o.loc)
                return 1;
            return 0;
        }
    }

    public static class grass implements Comparable<grass> {
        int loc;
        long val;
        long dist;
        long start;
        long end;

        public grass(int loc, long val) {
            this.loc = loc;
            this.val = val;
        }

        @Override
        public int compareTo(close.grass o) {
            return this.loc - o.loc;
        }
    }
}