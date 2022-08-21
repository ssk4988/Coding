import java.io.*;
import java.util.*;

public class a {
    public static int t;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int s = Integer.parseInt(tokenizer.nextToken()) - 1;
        t = Integer.parseInt(tokenizer.nextToken()) - 1;
        node[] ns = new node[2 * n];
        for (int i = 0; i < n; i++) {
            ns[i] = new node();
            ns[i + n] = new node();
            ns[i].id = ns[i + n].id = i;
        }
        int m = Integer.parseInt(in.readLine());
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            int w = Integer.parseInt(tokenizer.nextToken());
            if (!ns[a].ns.containsKey(ns[b])) {
                ns[a].ns.put(ns[b], new TreeSet<>());
            }
            if (!ns[b].ns.containsKey(ns[a])) {
                ns[b].ns.put(ns[a], new TreeSet<>());
            }
            ns[a].ns.get(ns[b]).add(w);
            ns[b].ns.get(ns[a]).add(w);
        }
        m = Integer.parseInt(in.readLine());
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1 + n;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1 + n;
            int w = Integer.parseInt(tokenizer.nextToken());
            if (!ns[a].ns.containsKey(ns[b])) {
                ns[a].ns.put(ns[b], new TreeSet<>());
            }
            if (!ns[b].ns.containsKey(ns[a])) {
                ns[b].ns.put(ns[a], new TreeSet<>());
            }
            ns[a].ns.get(ns[b]).add(w);
            ns[b].ns.get(ns[a]).add(w);
        }
        PriorityQueue<node> q = new PriorityQueue<>((o1, o2) -> {
            if (o1.dist < o2.dist)
                return -1;
            if (o1.dist == o2.dist)
                return 0;
            return 1;
        });
        for (int i = 0; i < 2*n; i++) {
            ns[i].dist = Long.MAX_VALUE;
            if (ns[i].id == t)
                ns[i].dist = 0;
            q.add(ns[i]);
        }
        while (!q.isEmpty()) {
            node n1 = q.poll();
            if (n1.visited)
                continue;
            n1.visited = true;
            for (node n2 : n1.ns.keySet()) {
                if (!n2.visited && n2.dist > n1.dist + n1.ns.get(n2).first()) {
                    n2.dist = n1.dist + n1.ns.get(n2).first();
                    q.add(n2);
                }
            }
        }
        for (int i = 0; i < ns.length; i++) {
            ns[i].visited = false;
            ns[i].dist = 0;
            for (node n1 : ns[i].ns.keySet()) {
                if (n1.dist < ns[i].dist) {
                    ns[i].e.put(ns[i < n ? n1.id + n : n1.id], ns[i].ns.get(n1).last());
                }
            }
        }
        
        System.out.println(dfs(ns[s]));

        in.close();
    }

    public static long dfs(node cur) {
        if(cur.v == 1) return -1;
        if(cur.v == 2) return cur.dist;
        cur.v = 1;
        for (node n1 : cur.e.keySet()) {
            long l1 = dfs(n1);
            if (l1 == -1){
                return -1;
            }
            cur.dist = Math.max(cur.dist, l1 + cur.e.get(n1));
        }
        cur.v = 2;
        return cur.dist;
    }

    public static class node {
        int id;
        Map<node, TreeSet<Integer>> ns = new HashMap<>();
        long dist;
        Map<node, Integer> e = new HashMap<>();
        boolean visited = false;
        int v = 0;
    }
}