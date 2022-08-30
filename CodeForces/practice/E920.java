import java.io.*;
import java.util.*;

public class E920 {
    static ArrayList<Integer>[] edges;
    static ArrayList<HashSet<Integer>> components;
    static TreeSet<Integer> left;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        edges = new ArrayList[n];
        components = new ArrayList<>();
        left = new TreeSet<>();
        for (int i = 0; i < n; i++) {
            edges[i] = new ArrayList<>();
            left.add(i);
        }
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            edges[a].add(b);
            edges[b].add(a);
        }
        while (!left.isEmpty()) {
            components.add(new HashSet<>());
            HashSet<Integer> set = new HashSet<>();
            set.addAll(edges[left.first()]);
            dfs(left.first(), set);
        }
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < components.size(); i++) {
            ans.add(components.get(i).size());
        }
        Collections.sort(ans);
        out.append(components.size() + "\n");
        for (int i : ans) {
            out.append(i + " ");
        }
        out.append("\n");
        System.out.print(out);
        in.close();
    }

    public static void dfs(int node, HashSet<Integer> not) {
        left.remove(node);
        int c = components.size() - 1;
        components.get(c).add(node);
        int cur = node;
        ArrayList<Integer> rem = new ArrayList<>();
        for(int i : not){
            if(!edges[node].contains(i)){
                rem.add(i);
            }
        }
        for(int i : rem){
            not.remove(i);
            left.remove(i);
            components.get(c).add(i);
        }
        while (true) {
            Integer l = left.higher(cur);
            if (l == null)
                return;
            cur = (int)l;
            if (!not.contains(cur)) {
                dfs(cur, not);
                return;
            }
        }
    }
}