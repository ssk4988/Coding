import java.io.*;
import java.util.*;

public class farm {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int q = Integer.parseInt(tokenizer.nextToken());
        component[] components = new component[n];
        node[] nodes = new node[n];
        ArrayList<Integer> u1 = new ArrayList<>();
        ArrayList<Integer> v1 = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            nodes[i] = new node(i);
            components[i] = new component(i);
            components[i].set.add(nodes[i]);
            components[i].numActive = 1;
            nodes[i].c = components[i];
        }
        // what if 2 roads added between same locations
        // what if disconnect but both sides are not relevant
        for (int i = 0; i < q; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            String s = tokenizer.nextToken();
            if (s.equals("A")) {
                int u = Integer.parseInt(tokenizer.nextToken()) - 1;
                int v = Integer.parseInt(tokenizer.nextToken()) - 1;
                nodes[u].neighbors.add(nodes[v]);
                nodes[v].neighbors.add(nodes[u]);
                u1.add(u);
                v1.add(v);
                if (nodes[u].c != nodes[v].c) {
                    if (nodes[v].c.set.size() < nodes[u].c.set.size()) {
                        int temp = u;
                        u = v;
                        v = temp;
                    }
                    nodes[u].c.set.addAll(nodes[v].c.set);
                    nodes[u].c.numActive += nodes[v].c.numActive;
                    for (node n2 : nodes[v].c.set) {
                        n2.c = nodes[u].c;
                    }
                }
            } else if (s.equals("D")) {
                int v = Integer.parseInt(tokenizer.nextToken()) - 1;
                if (nodes[v].active) {
                    nodes[v].active = false;
                    nodes[v].c.numActive--;
                    if (nodes[v].c.numActive <= 0) {
                        for (node n2 : nodes[v].c.set) {
                            if (n2.lastRelevant == -1) {
                                n2.lastRelevant = i;
                            }
                        }
                    }
                }
            } else {
                // s == R
                int k = Integer.parseInt(tokenizer.nextToken()) - 1;
                int u = u1.get(k);
                int v = v1.get(k);
                nodes[u].neighbors.remove(nodes[v]);
                nodes[v].neighbors.remove(nodes[u]);
                if(nodes[u].c.numActive <= 0) continue;
                if(nodes[u].c.id == nodes[u].id){
                    int temp = u;
                    u = v;
                    v = temp;
                }
                component c = nodes[v].c;
                components[u] = new component(u);
                boolean[] visited = new boolean[n];
                ArrayDeque<node> qu = new ArrayDeque<>();
                qu.add(nodes[u]);
                while(!qu.isEmpty()){
                    node n2 = qu.poll();
                    if(visited[n2.id]) continue;
                    visited[n2.id] = true;
                    components[u].set.add(n2);
                    n2.c = components[u];
                    c.set.remove(n2);
                    if(n2.active){
                        components[u].numActive++;
                        c.numActive--;
                    }
                    for(node n3 : n2.neighbors){
                        if(!visited[n3.id]){
                            qu.add(n3);
                        }
                    }
                }
                if(nodes[u].c.numActive <= 0){
                    for (node n2 : nodes[u].c.set) {
                        if (n2.lastRelevant == -1) {
                            n2.lastRelevant = i;
                        }
                    }
                }
                if(nodes[v].c.numActive <= 0){
                    for (node n2 : nodes[v].c.set) {
                        if (n2.lastRelevant == -1) {
                            n2.lastRelevant = i;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < n; i++){
            if(nodes[i].lastRelevant == -1){
                nodes[i].lastRelevant = q;
            }
            System.out.println(nodes[i].lastRelevant);
        }

        in.close();
    }

    public static class node {
        int id;
        boolean active = true;
        int lastRelevant = -1;
        component c = null;
        ArrayList<node> neighbors = new ArrayList<>();

        public node(int id) {
            this.id = id;
        }
    }

    public static class component {
        int id;
        int numActive = 0;
        Set<node> set = new HashSet<>();

        public component(int id) {
            this.id = id;
        }
    }
}