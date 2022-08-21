import java.io.*;
import java.util.*;

public class p002 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        card[] original = new card[n];
        TreeMap<Integer, Integer>[] m = new TreeMap[3];
        TreeMap<Integer, Set<card>>[] m2 = new TreeMap[3];
        for (int i = 0; i < m.length; i++) {
            m[i] = new TreeMap<>();
            m2[i] = new TreeMap<>();
        }
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            original[i] = new card(Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()),
                    Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
            for (int j = 0; j < 3; j++) {
                if (!m[j].containsKey(original[i].angle[j])) {
                    m[j].put(original[i].angle[j], 0);
                }
                m[j].put(original[i].angle[j], m[j].get(original[i].angle[j]) + 1);
                if (!m2[j].containsKey(original[i].angle[j])) {
                    m2[j].put(original[i].angle[j], new HashSet<>());
                }
                m2[j].get(original[i].angle[j]).add(original[i]);
            }
        }
        TreeSet<card> q = new TreeSet<>(new comp());
        for (int i = 0; i < n; i++) {
            original[i].calcScore(m);
            q.add(original[i]);
        }
        StringBuilder b = new StringBuilder();
        while (!q.isEmpty()) {
            card c = q.first();
            q.remove(c);
            if (c.used)
                continue;
            c.used = true;
            Set<card> change = new HashSet<>();
            b.append(c.id + "\n");
            for (int i = 0; i < 3; i++) {
                m[i].put(c.angle[i], m[i].get(c.angle[i]) - 1);
                m2[i].get(c.angle[i]).remove(c);
                if (m[i].get(c.angle[i]) == 0) {
                    int higherKey = m[i].higherKey(c.angle[i]) == null ? m[i].firstKey() : m[i].higherKey(c.angle[i]);
                    if (m[i].get(higherKey) <= 1) {
                        for (card c1 : m2[i].get(higherKey)) {
                            change.add(c1);
                        }
                    }
                    int lowerKey = m[i].lowerKey(c.angle[i]) == null ? m[i].lastKey() : m[i].lowerKey(c.angle[i]);
                    if (m[i].get(lowerKey) <= 1) {
                        for (card c1 : m2[i].get(lowerKey)) {
                            change.add(c1);
                        }
                    }
                    m[i].remove(c.angle[i]);
                } else if (m[i].get(c.angle[i]) == 1) {
                    for (card c1 : m2[i].get(c.angle[i])) {
                        change.add(c1);
                    }
                }
            }
            for (card c1 : change) {
                while (q.contains(c1)) {
                    q.remove(c1);
                }
                c1.calcScore(m);
                q.add(c1);
            }
        }
        System.out.print(b);
        in.close();
    }

    public static class comp implements Comparator<card> {
        @Override
        public int compare(p002.card o1, p002.card o2) {
            if (o1.score == o2.score) {
                return o2.id - o1.id;
            }
            return o1.score - o2.score;
        }
    }

    public static class card {
        int id;
        boolean used = false;
        int[] angle = new int[3];
        int score = 0;

        public card(int r, int g, int b, int id) {
            angle[0] = r;
            angle[1] = g;
            angle[2] = b;
            this.id = id;
        }

        public void calcScore(TreeMap<Integer, Integer>[] m) {
            score = 0;
            for (int i = 0; i < 3; i++) {
                int upper = 0;
                int lower = 0;
                if (m[i].get(angle[i]) > 1) {
                    upper = lower = angle[i];
                } else {
                    upper = m[i].higherKey(angle[i]) == null ? m[i].firstKey() : m[i].higherKey(angle[i]);
                    lower = m[i].lowerKey(angle[i]) == null ? m[i].lastKey() : m[i].lowerKey(angle[i]);
                }
                score += angle[i] - lower;
                if (lower > angle[i]) {
                    score += 360;
                }
                score += upper - angle[i];
                if (upper < angle[i]) {
                    score += 360;
                }
            }
        }
    }
}