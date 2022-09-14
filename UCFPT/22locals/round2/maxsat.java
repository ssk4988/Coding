import java.io.*;
import java.util.*;

public class maxsat {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int s = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        HashSet<Integer>[] c = new HashSet[s];
        int[][] sat = new int[n][s];
        // int[] each = new int[s];
        int[] a = new int[n];
        int maxsat = 0;
        for (int i = 0; i < s; i++) {
            c[i] = new HashSet<>();
        }
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int best = 0;
            for (int j = 0; j < s; j++) {
                sat[i][j] = Integer.parseInt(tokenizer.nextToken());
                if (sat[i][j] > sat[i][best]) {
                    best = j;
                }
            }
            a[i] = best;
            // each[best]++;
            c[best].add(i);
            maxsat += sat[i][best];
        }
        PriorityQueue<edge> q = new PriorityQueue<>();
        for (int i = 0; i < s; i++) {
            if (c[i].size() < k) {
                for (int j = 0; j < n; j++) {
                    if (c[i].contains(j))
                        continue;
                    q.add(new edge(j, a[j], i, sat[j][i] - sat[j][a[j]]));
                }
            }
        }
        while (!q.isEmpty()) {
            edge e = q.poll();
            if (a[e.s] != e.i || c[e.j].size() >= k)// || c[e.i].size() - 1 < k) // not valid/needed move
                continue;
            maxsat -= e.c;
            c[e.i].remove(e.s);
            c[e.j].add(e.s);
            a[e.s] = e.j;
            if(c[e.i].size() < k){
                for(int j = 0; j < n; j++){
                    if(c[e.i].contains(j))continue;
                    //q.add(e)
                }
            }
        }
        System.out.println(maxsat);
    }

    public static class edge implements Comparable<edge> {
        int s = 0;
        int i = 0;
        int j = 0;
        int c = 0;

        public edge(int s, int i, int j, int c) {
            this.s = s;
            this.i = i;
            this.j = j;
            this.c = c;
        }

        @Override
        public int compareTo(maxsat.edge o) {
            return this.c - o.c;
        }
    }
}