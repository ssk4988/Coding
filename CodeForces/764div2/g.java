import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder o= new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            in.readLine();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int vertices = Integer.parseInt(tokenizer.nextToken());
            int edges = Integer.parseInt(tokenizer.nextToken());
            node[] nodes = new node[vertices];
            for(int i = 0; i < nodes.length; i++){
                nodes[i] = new node(i);
            }
            int maxWeight = 0;
            for(int i= 0; i < edges; i++){
                tokenizer = new StringTokenizer(in.readLine());
                node n1 = nodes[Integer.parseInt(tokenizer.nextToken())-1];
                node n2 = nodes[Integer.parseInt(tokenizer.nextToken())-1];
                int weight = Integer.parseInt(tokenizer.nextToken());
                edge e = new edge(n1, n2, weight);
                n1.edges.add(e);
                n2.edges.add(e);
                maxWeight |= weight;
            }
            
            int numbit = 0;
            while((1 << numbit) <= maxWeight){
                numbit++;
            }
            numbit--;
            int minOr = maxWeight;
            for(int b = numbit; b >= 0; b--){
                int bit = (1 << b);
                if((bit & maxWeight) != bit) continue;
                for(node n : nodes){
                    n.edges2 = new ArrayList<>(n.edges.size());
                    n.visited = false;
                    for(edge e : n.edges){
                        if((bit & e.weight) != bit){
                            n.edges2.add(e);
                        }
                    }
                }
                dfs(nodes[0]);
                boolean travelled = true;
                for(int i = 0; i < nodes.length; i++){
                    travelled = travelled && nodes[i].visited;
                }
                if(travelled){
                    for(int i = 0; i < nodes.length; i++){
                        nodes[i].edges = nodes[i].edges2;
                    }
                    minOr &= ~bit;
                }
            }
            o.append(minOr + "\n");
        }
        System.out.print(o);
        in.close();
        out.close();
    }
    public static void dfs(node n){
        n.visited = true;
        for(edge e : n.edges2){
            if(!e.other(n).visited) dfs(e.other(n));
        }
    }
    public static class node{
        int id;
        boolean visited = false;
        ArrayList<edge> edges = new ArrayList<>();
        ArrayList<edge> edges2 = new ArrayList<>();
        public node(int id){
            this.id = id;
        }
    }
    public static class edge{
        int id;
        node n1;
        node n2;
        int weight;
        public edge(node n1, node n2, int weight){
            this.n1 = n1;
            this.n2 = n2;
            this.weight = weight;
        }
        public node other(node o){
            if(n1 == o) return n2;
            return n1;
        }
    }
}