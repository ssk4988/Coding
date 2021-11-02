/*
ID: ssk49881
LANG: JAVA
TASK: mountains
*/

import java.io.*;
import java.util.*;

public class mountains {
    public static void main(String[] args) throws Exception {
        long start = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("mountains.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mountains.out")));

        int numMountains = Integer.parseInt(in.readLine());
        ArrayList<Tuple> mountList = new ArrayList<>();
        Tuple[] mountains = new Tuple[numMountains];
        boolean[] above = new boolean[numMountains];
        Arrays.fill(above, true);
        for (int i = 0; i < numMountains; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            mountains[i] = new Tuple(x, y);
            mountList.add(new Tuple(x, y));
        }
        Arrays.sort(mountains);
        Collections.sort(mountList);
        // System.out.println(System.currentTimeMillis() - start);
        for (int i = 0; i < mountList.size(); i++) {
            for (int j = i - 1; j >= 0; j--) {
                Tuple m1 = mountList.get(i);
                Tuple m2 = mountList.get(j);
                if (m2.x < m1.x - m1.y)
                    break;
                if (m2.y <= m1.y - (m1.x - m2.x)) {
                    mountList.remove(j);
                    i--;
                }
            }
            for (int j = i + 1; j < mountList.size(); j++) {
                Tuple m1 = mountList.get(i);
                Tuple m2 = mountList.get(j);
                if (m2.x > m1.y + m1.x)
                    break;
                if (m2.y <= m1.y + (m1.x - m2.x)) {
                    mountList.remove(j);
                    j--;
                }

            }
            // if (i % 1000 == 0)
            // System.out.println(i + " " + (System.currentTimeMillis() - start));
        }
        // System.out.println(System.currentTimeMillis() - start);
        out.println(mountList.size());
        in.close();
        out.close();
    }

    public static class Tuple implements Comparable<Tuple> {
        int x;
        int y;

        public Tuple(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(mountains.Tuple o) {
            return this.x - o.x;
        }
    }
}