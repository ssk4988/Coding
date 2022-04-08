import java.io.*;
import java.util.*;

public class hay {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] j = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        long k = n + 1;
        node[] nodes = new node[n + 1];
        for (int i = 0; i < nodes.length; i++) {
            nodes[i] = new node(i);
        }
        for (int i = 0; i < n; i++) {
            j[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
            nodes[i].parent = nodes[j[i] + 1];
            nodes[j[i] + 1].children.add(nodes[i]);
        }
        for (int i = 0; i < nodes.length; i++) {
            Collections.sort(nodes[i].children);
        }
        int a = n;
        dfs(nodes[n], a, 0);
        int maxdepth = nodes[0].depth;
        System.out.println(k);
        for (int i = 0; i < n; i++) {
            nodes[i].depth = maxdepth - nodes[i].depth;
            // System.out.println(i + " " + nodes[i].depth + " " + nodes[i].a + " " +
            // (nodes[i].depth * k + nodes[i].a));
            System.out.println(nodes[i].depth * k + nodes[i].a);
        }
        // System.out.println(Arrays.toString(arr));
        in.close();
    }

    public static int dfs(node n, int a, int depth) {
        n.a = a;
        n.depth = depth;
        a--;
        for (node n2 : n.children) {
            a = dfs(n2, a, depth + 1);
        }
        return a;
    }

    public static class node implements Comparable<node> {
        int id;
        node parent = null;
        int depth = 0;
        ArrayList<node> children = new ArrayList<>();
        int a = 0;

        public node(int id) {
            this.id = id;
        }

        @Override
        public int compareTo(hay.node o) {
            return o.id - this.id;
        }
    }
}