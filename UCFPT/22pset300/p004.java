import java.io.*;
import java.util.*;

public class p004 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        Map<Integer, Map<Integer, spot>> m = new HashMap<>();
        spot[] spots = new spot[2 * n];
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            spot s1 = new spot(i, Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
            spot s2 = new spot(i, Integer.parseInt(tokenizer.nextToken()), Integer.parseInt(tokenizer.nextToken()));
            s1.other = s2;
            s2.other = s1;
            if (!m.containsKey(s1.r)) {
                m.put(s1.r, new HashMap<>());
            }
            m.get(s1.r).put(s1.c, s1);
            if (!m.containsKey(s2.r)) {
                m.put(s2.r, new HashMap<>());
            }
            m.get(s2.r).put(s2.c, s2);
            spots[2 * i] = s1;
            spots[2 * i + 1] = s2;
        }
        boolean works = true;
        int[] dr = new int[] { 1, 0, -1, 0 };
        int[] dc = new int[] { 0, 1, 0, -1 };
        for (int i = 0; i < spots.length; i++) {
            for (int j = 0; j < dr.length; j++) {
                int r1 = spots[i].r + dr[j];
                int c1 = spots[i].c + dc[j];
                spot n1 = (m.containsKey(r1) && m.get(r1).containsKey(c1)) ? m.get(r1).get(c1) : null;
                if (n1 != null && spots[i].other != n1) {
                    spots[i].neighbors.add(n1);
                }
            }
            if (spots[i].neighbors.size() == 0)
                works = false;
        }
        spot source = new spot(-1, -1, -1);
        spot sink = new spot(-2, -1, -1);
        for (int i = 0; i < spots.length && works; i++) {
            if (spots[i].visited)
                continue;
            ArrayDeque<spot> q = new ArrayDeque<>();
            spots[i].parity = true;
            q.add(spots[i]);
            while (!q.isEmpty()) {
                spot s = q.poll();
                if (s.visited)
                    continue;
                s.visited = true;
                if (s.parity) {
                    source.neighbors.add(s);
                    source.w.put(s, 1);
                    s.neighbors.add(source);
                    s.w.put(source, 0);
                } else {
                    sink.neighbors.add(s);
                    sink.w.put(s, 0);
                    s.neighbors.add(sink);
                    s.w.put(sink, 1);
                }
                for (spot s1 : s.neighbors) {
                    if (s1 == sink || s1 == source)
                        continue;
                    if (!s1.visited) {
                        s1.parity = !s.parity;
                        q.add(s1);
                    }
                }
            }
        }
        for (int i = 0; i < spots.length && works; i++) {
            for (spot s1 : spots[i].neighbors) {
                if (s1 == source || s1 == sink)
                    continue;
                spots[i].w.put(s1, spots[i].parity ? 1 : 0);
            }
        }
        int max_flow = 0;
        while (bfs(source, sink, spots) && works) {
            int min = Integer.MAX_VALUE;
            for (spot v = sink; v.parent != null; v = v.parent) {
                min = Math.min(min, v.parent.w.get(v));
            }
            max_flow += min;
            for (spot v = sink; v.parent != null; v = v.parent) {
                v.w.put(v.parent, v.w.get(v.parent) + min);
                v.parent.w.put(v, v.parent.w.get(v) - min);
            }
        }
        int cnter = 0;
        for (int i = 0; i < spots.length && works; i++) {
            int sum = 0;
            for (Map.Entry<spot, Integer> e : spots[i].w.entrySet()) {
                if (e.getKey() != sink && e.getKey() != source) {
                    if ((spots[i].parity && e.getValue() == 0) || (!spots[i].parity && e.getValue() == 1)) {
                        sum++;
                        if (spots[i].val == -1) {
                            spots[i].val = cnter;
                            e.getKey().val = cnter;
                            cnter++;
                        }
                    }

                }
            }
            works &= sum == 1;
        }
        if (works) {
            StringBuilder b = new StringBuilder();
            for (int i = 0; i < n; i++) {
                b.append(spots[2 * i].val + " " + spots[2 * i + 1].val + "\n");
            }
            System.out.print(b);
        } else {
            System.out.println("impossible");
        }
        in.close();
    }

    public static boolean bfs(spot start, spot end, spot[] spots) {
        ArrayDeque<spot> q = new ArrayDeque<>();
        for (spot s : spots) {
            s.parent = null;
            s.visited = false;
        }
        start.parent = null;
        start.visited = false;
        end.parent = null;
        end.visited = false;
        q.add(start);
        while (!q.isEmpty()) {
            spot s = q.poll();
            if (s.visited)
                continue;
            s.visited = true;
            if (s == end)
                return true;
            for (spot s1 : s.neighbors) {
                if (!s1.visited && s.w.get(s1) > 0) {
                    s1.parent = s;
                    q.add(s1);
                }
            }
        }

        return false;
    }

    public static class comp implements Comparator<spot> {
        @Override
        public int compare(p004.spot o1, p004.spot o2) {
            return o1.neighbors.size() - o2.neighbors.size();
        }
    }

    public static class spot {
        int id = 0;
        spot other = null;
        boolean parity = true;
        boolean visited = false;
        spot parent = null;
        int r = 0;
        int c = 0;
        ArrayList<spot> neighbors = new ArrayList<>();
        Map<spot, Integer> w = new HashMap<>();
        int val = -1;
        boolean used = false;

        public spot(int id, int r, int c) {
            this.id = id;
            this.r = r;
            this.c = c;
        }
    }
}