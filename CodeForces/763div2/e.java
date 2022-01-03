import java.io.*;
import java.util.*;

public class e {
    public static int rem;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        String lab = in.readLine();
        node[] list = new node[n];
        for (int i = 0; i < n; i++) {
            list[i] = new node(i, lab.substring(i, i + 1));
        }
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int left = Integer.parseInt(tokenizer.nextToken()) - 1;
            int right = Integer.parseInt(tokenizer.nextToken()) - 1;
            if (left != -1) {
                list[i].left = list[left];
                list[left].parent = list[i];
            }
            if (right != -1) {
                list[i].right = list[right];
                list[right].parent = list[i];
            }
        }
        node[] order = new node[n];
        inorder(order, 0, list[0]);
        for (int i = 0; i < n; i++) {
            order[i].inorder = i;
        }
        rem = k;
        ArrayList<String> vals = new ArrayList<>();
        for (int i = order.length - 1; i >= 0; i--) {
            if (vals.size() == 0 || !order[i].label.equals(vals.get(vals.size() - 1))) {
                vals.add(order[i].label);
            }
            order[i].good = vals.size() > 1 && vals.get(vals.size() - 1).compareTo(vals.get(vals.size() - 2)) < 0;
        }
        dfs(list[0], 1);
        StringBuilder b = new StringBuilder();
        for (int i = 0; i < order.length; i++) {
            b.append(order[i].label);
            if (order[i].used) {
                b.append(order[i].label);
            }
        }
        System.out.println(b);
        in.close();
        out.close();
    }
    public static void dfs(node n, int cost) {
        if (n == null || n.used)
            return;
        dfs(n.left, cost + 1);
        if (cost <= rem && n.good && !n.used) {
            rem -= cost;
            update(n);
        }
        if (n.used) {
            dfs(n.right, 1);
        }
    }

    public static void update(node n) {
        n.used = true;
        if (n.parent != null && !n.parent.used) {
            update(n.parent);
        }
    }

    public static int inorder(node[] order, int index, node n) {
        if (n != null) {
            index = inorder(order, index, n.left);
            order[index++] = n;
            index = inorder(order, index, n.right);
        }
        return index;
    }

    public static class node {
        int id;
        String label;
        node left = null;
        node right = null;
        node parent = null;
        boolean used = false;
        boolean good = false;
        int inorder = 0;

        public node(int id, String label) {
            this.id = id;
            this.label = label;
        }
    }
}