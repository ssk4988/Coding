import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        node[] nodes = new node[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numBlack = 0;
        for (int i = 0; i < n; i++) {
            nodes[i] = new node(i, Integer.parseInt(tokenizer.nextToken()) == 1);
            if (nodes[i].black) {
                numBlack++;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            nodes[i1].neighbors.add(nodes[i2]);
            nodes[i2].neighbors.add(nodes[i1]);
        }
        dfs(nodes[0], null);
        for (int i = 0; i < n; i++) {
            //System.out.println("node " + (i + 1) + ": " + nodes[i].bNested);
            for (node n2 : nodes[i].neighbors) {
                if ((nodes[i].parent == n2 ? numBlack - nodes[i].bNested : n2.bNested) >= 2) {
                    //nodes[i].access.add(n2);
                    n2.access.add(nodes[i]);
                    //System.out.println("adding: " + (i + 1) + " to " + (n2.id + 1));
                }
            }
        }
        ArrayDeque<node> queue = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            if (!nodes[i].black)
                continue;
            for (node n2 : nodes[i].neighbors) {
                nodes[i].access.add(n2);
                //n2.access.add(nodes[i]);
            }
            queue.add(nodes[i]);
        }
        while (!queue.isEmpty()) {
            node n2 = queue.poll();
            if (n2.visited)
                continue;
            n2.visited = true;
            for (node n3 : n2.access) {
                if (n3.visited)
                    continue;
                queue.add(n3);
            }
        }
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < n; i++) {
            b.append((nodes[i].visited ? 1 : 0) + (i < n - 1 ? " " : "\n"));
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static int dfs(node curr, node prev) {
        curr.bNested += curr.black ? 1 : 0;
        for (node n : curr.neighbors) {
            if (n == prev) {
                continue;
            }
            n.parent = curr;
            curr.bNested += dfs(n, curr);
        }
        return curr.bNested;
    }

    public static class node {
        int id;
        boolean black;
        int bNested = 0;
        boolean visited = false;
        node parent = null;
        ArrayList<node> neighbors = new ArrayList<>();
        ArrayList<node> access = new ArrayList<>();

        public node(int id, boolean black) {
            this.id = id;
            this.black = black;
        }
    }
}