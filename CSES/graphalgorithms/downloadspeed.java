import java.io.*;
import java.util.*;

public class downloadspeed {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        node[] nodes = new node[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new node(i);
        }
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            long c = Integer.parseInt(tokenizer.nextToken());
            if (!nodes[a].neighbors.contains(nodes[b])) {
                nodes[a].neighbors.add(nodes[b]);
                nodes[a].weights.put(nodes[b], c);
            } else {
                nodes[a].weights.put(nodes[b], nodes[a].weights.get(nodes[b]) + c);
            }
            if (!nodes[b].neighbors.contains(nodes[a])) {
                nodes[b].neighbors.add(nodes[a]);
                nodes[b].weights.put(nodes[a], 0L);
            }
        }
        long max_flow = 0;
        while (bfs(nodes[0], nodes[n - 1], nodes)) {
            long min = Long.MAX_VALUE;
            for (node v = nodes[n - 1]; v.parent != null; v = v.parent) {
                min = Math.min(min, v.parent.weights.get(v));
            }
            max_flow += min;
            for (node v = nodes[n - 1]; v.parent != null; v = v.parent) {
                v.weights.put(v.parent, v.weights.get(v.parent) + min);
                v.parent.weights.put(v, v.parent.weights.get(v) - min);
            }
        }
        System.out.println(max_flow);
        in.close();
    }

    public static boolean bfs(node start, node end, node[] nodes) {
        ArrayDeque<node> q = new ArrayDeque<>();
        for (node n : nodes) {
            n.parent = null;
            n.visited = false;
        }
        q.add(start);
        while (!q.isEmpty()) {
            node n = q.poll();
            if (n.visited)
                continue;
            n.visited = true;
            if (n == end)
                return true;
            for (node n2 : n.neighbors) {
                if (!n2.visited && n.weights.get(n2) > 0) {
                    n2.parent = n;
                    q.add(n2);
                }
            }
        }

        return false;
    }

    public static class node {
        node parent = null;
        int id;
        boolean visited = false;
        Set<node> neighbors = new HashSet<>();
        Map<node, Long> weights = new HashMap<>();

        public node(int id) {
            this.id = id;
        }
    }
}