/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int count = 0; count < numcases; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int casenum = Integer.parseInt(tokenizer.nextToken());
            int numNodes = Integer.parseInt(tokenizer.nextToken());
            int numEdges = Integer.parseInt(tokenizer.nextToken());
            Node[] nodes = new Node[numNodes];
            for (int i = 0; i < numNodes; i++) {
                nodes[i] = new Node();
            }
            for (int i = 0; i < numEdges; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                int first = Integer.parseInt(tokenizer.nextToken()) - 1;
                int second = Integer.parseInt(tokenizer.nextToken()) - 1;
                nodes[first].children.add(nodes[second]);
                nodes[second].parents.add(nodes[first]);
            }
            for (int i = 0; i < numNodes; i++) {
                solve(nodes[i]);
            }
            int answer = 0;
            for (int i = 0; i < numNodes; i++) {
                answer = Math.max(answer, nodes[i].order);
            }
            System.out.printf("%d %d%n", casenum, answer);
        }

        in.close();
        out.close();
    }

    public static void solve(Node n) {
        if (n.order != -1)
            return;
        if (n.parents.size() == 0) {
            n.order = 1;
            return;
        }
        int maxorder = 0;
        int nummax = 0;
        for (Node p : n.parents) {
            solve(p);
            if (maxorder < p.order) {
                maxorder = p.order;
                nummax = 1;
            } else if (maxorder == p.order) {
                nummax++;
            }
        }
        n.order = nummax > 1 ? maxorder + 1 : maxorder;
    }

    public static class Node {
        int order = -1;
        Set<Node> parents = new HashSet<>();
        Set<Node> children = new HashSet<>();
    }
}