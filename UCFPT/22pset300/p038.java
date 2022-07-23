import java.io.*;
import java.util.*;

public class p038 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int q = Integer.parseInt(tokenizer.nextToken());
        component[] components = new component[n];
        node[] nodes = new node[n];
        ArrayList<Integer> u1 = new ArrayList<>();
        ArrayList<Integer> v1 = new ArrayList<>();
        ArrayList<Boolean> droad = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            nodes[i] = new node(i);
            nodes[i].lastRelevant = q;
            components[i] = new component(i);
            components[i].stuff.add(nodes[i]);
            components[i].size = 1;
            nodes[i].c = components[i];
        }
        boolean[] deactivated = new boolean[n];
        ArrayList<String> input = new ArrayList<>();
        ArrayList<Integer> dq = new ArrayList<>();
        // what if 2 roads added between same locations
        // what if disconnect but both sides are not relevant
        for (int i = 0; i < q; i++) {
            String s1 = in.readLine();
            input.add(s1);
            tokenizer = new StringTokenizer(s1);
            String s = tokenizer.nextToken();
            if (s.equals("A")) {
                int u = Integer.parseInt(tokenizer.nextToken()) - 1;
                int v = Integer.parseInt(tokenizer.nextToken()) - 1;
                u1.add(u);
                v1.add(v);
                droad.add(false);
            } else if (s.equals("D")) {
                int v = Integer.parseInt(tokenizer.nextToken()) - 1;
                deactivated[v] = true;
                dq.add(v);
            } else {
                // s == R
                int k = Integer.parseInt(tokenizer.nextToken()) - 1;
                droad.set(k, true);

            }
        }
        for (int i = 0; i < n; i++) {
            if (!deactivated[i]) {
                nodes[i].lastRelevant = 0;
                nodes[i].c.numActive++;
            }
        }
        for (int i = 0; i < droad.size(); i++) {
            if (!droad.get(i)) {
                unite(0, nodes[u1.get(i)], nodes[v1.get(i)]);
            }
        }
        for (int i = 0; i < input.size(); i++) {
            tokenizer = new StringTokenizer(input.get(input.size() - 1 - i));
            String s = tokenizer.nextToken();
            if (s.equals("A")) {
            } else if (s.equals("D")) {
                int v = Integer.parseInt(tokenizer.nextToken()) - 1;
                if (nodes[v].c.numActive <= 0) {
                    for (node c : nodes[v].c.stuff) {
                        c.lastRelevant = Math.min(c.lastRelevant, i + 1);
                    }
                    nodes[v].c.stuff = new ArrayList<>();
                }
                nodes[v].c.numActive++;

            } else {
                // s == R
                int k = Integer.parseInt(tokenizer.nextToken()) - 1;
                int u = u1.get(k);
                int v = v1.get(k);
                unite(i + 1, nodes[u], nodes[v]);

            }
        }
        
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < n; i++) {
            nodes[i].lastRelevant = Math.min(nodes[i].lastRelevant, q);
            b.append((q - nodes[i].lastRelevant)+"\n");
        }
        System.out.print(b);

        in.close();
    }

    public static void unite(int turn, node n1, node n2) {
        if (n1.c == n2.c)
            return;
        component c1 = null;
        component c2 = null;
        if (n1.c.stuff.size() >= n2.c.stuff.size()) {
            c1 = n1.c;
            c2 = n2.c;
        } else {
            c1 = n2.c;
            c2 = n1.c;
        }
        if (c1.numActive <= 0 && c2.numActive > 0) {
            for (node n : c1.stuff) {
                n.lastRelevant = Math.min(turn, n.lastRelevant);
            }
        }
        if (c1.numActive > 0 && c2.numActive <= 0) {
            for (node n : c2.stuff) {
                n.lastRelevant = Math.min(turn, n.lastRelevant);
            }
        }
        for (node n : c2.stuff) {
            n.c = c1;
            c1.stuff.add(n);
        }
        if (c1.numActive > 0 || c2.numActive > 0) {
            c1.stuff = new ArrayList<>();
        }
        c1.numActive += c2.numActive;
        c1.size += c2.size;
        //c2.numActive = 0;
        c2.stuff = new ArrayList<>();
    }

    public static class node {
        int id;
        int lastRelevant = Integer.MAX_VALUE;
        component c = null;

        public node(int id) {
            this.id = id;
        }
    }

    public static class component {
        int id;
        int numActive = 0;
        int size = 0;
        ArrayList<node> stuff = new ArrayList<>();

        public component(int id) {
            this.id = id;
        }
    }
}