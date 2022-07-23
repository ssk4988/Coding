import java.io.*;
import java.util.*;

public class f {
    public static ArrayList<component> cs = new ArrayList<>();

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
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            nodes[i1].neighbors.add(nodes[i2]);
            nodes[i2].neighbors.add(nodes[i1]);
        }
        nodes[n - 1].a = true;
        nodes[n - 1].used = true;
        cs.add(new component(cs.size()));
        cs.get(0).children.add(nodes[n - 1]);
        nodes[n - 1].c = cs.get(0);
        for (node n2 : nodes[n - 1].neighbors) {
            if (n2.c == null) {
                cs.add(new component(cs.size()));
                dfs(n2);
            }
        }
        int max = -1;
        for (int i = 1; i < cs.size(); i++) {
            if (cs.get(i).children.size() > 0) {
                max = Math.max(max, cs.get(i).children.last().id);
            }
        }
        if (max != -1) {
            for (int i = 1; i < cs.size(); i++) {
                if (!cs.get(i).children.contains(nodes[max])) {
                    for (node n2 : cs.get(i).children) {
                        n2.a = true;
                    }
                }
                for (node n2 : cs.get(i).children) {
                    n2.used = true;
                }
            }
        }
        for(node n2 : nodes){
            if(!n2.used) n2.used = true;
        }
        StringBuilder b = new StringBuilder();
        for(int i = 0; i < n; i++){
            b.append(nodes[i].a ? 'A' : 'B');
        }
        System.out.println(b);
        in.close();
    }

    public static void dfs(node n) {
        n.c = cs.get(cs.size() - 1);
        cs.get(cs.size() - 1).children.add(n);
        for (node n2 : n.neighbors) {
            if (n2.c == null) {
                dfs(n2);
            }
        }
    }

    public static class node implements Comparable<node> {
        int id;
        ArrayList<node> neighbors = new ArrayList<>();
        boolean used = false;
        boolean a = false;
        component c = null;

        public node(int id) {
            this.id = id;
        }

        @Override
        public int compareTo(f.node o) {
            return this.id - o.id;
        }
    }

    public static class component {
        int id;
        public TreeSet<node> children = new TreeSet<>();

        public component(int id) {
            this.id = id;
        }
    }
}