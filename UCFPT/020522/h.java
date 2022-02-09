import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int mod = 11092019;
        node[] nodes =new node[n];
        for(int i = 0; i < n; i++){
            nodes[i] = new node(i, Integer.parseInt(in.readLine()), n);
        }
        for(int i = 1; i < n; i++){
            nodes[i].parent = nodes[Integer.parseInt(in.readLine())-1];
            nodes[i].parent.numchildren++;
            nodes[i].parent.children.add(nodes[i]);
        }
        ArrayDeque<node> q = new ArrayDeque<>();
        for(int i = 0; i < n; i++){
            if(nodes[i].csolved == nodes[i].numchildren){
                q.add(nodes[i]);
            }
        }
        while(!q.isEmpty()){
            node f = q.poll();

        }


        in.close();
        out.close();
    }
    
    public static class node{
        int id;
        long[] bit = null;
        int label = 0;
        int longest = 0;
        int numchildren = 0;
        int csolved = 0;
        node parent = null;
        ArrayList<node> children =new ArrayList<>();
        public node(int id, int label, int n){
            this.id = id;
            this.label = label;
        }
    }
}