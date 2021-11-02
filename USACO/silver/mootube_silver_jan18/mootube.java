/*
ID: ssk49881
LANG: JAVA
TASK: mootube
*/

import java.io.*;
import java.util.*;

public class mootube {
    public static Video[] videos;
    public static int numVideos;
    public static int[][] distance;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("mootube.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numVideos = Integer.parseInt(tokenizer.nextToken());
        int numQueries = Integer.parseInt(tokenizer.nextToken());
        videos = new Video[numVideos];
        for (int i = 0; i < numVideos; i++) {
            videos[i] = new Video(i, numVideos);
        }
        distance = new int[numVideos][numVideos];
        for (int[] i : distance) {
            Arrays.fill(i, Integer.MAX_VALUE);
        }
        for (int i = 0; i < numVideos - 1; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int dist = Integer.parseInt(tokenizer.nextToken());
            videos[first].neighbors.add(second);
            videos[second].neighbors.add(first);
            videos[first].distance[second] = dist;
            videos[second].distance[first] = dist;
        }
        boolean[] done = new boolean[numVideos];
        for (int i = 0; i < numQueries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(tokenizer.nextToken());
            int id = Integer.parseInt(tokenizer.nextToken()) - 1;
            int num = 0;
            ArrayList<Integer> queue = new ArrayList<>();
            ArrayList<Integer> parents = new ArrayList<>();
            queue.add(id);
            parents.add(-1);
            while(!queue.isEmpty()){
                int next = queue.remove(0);
                int parent = parents.remove(0);
                for(int neighbor : videos[next].neighbors){
                    if(neighbor != parent && videos[neighbor].distance[next] >= k){
                        num++;
                        queue.add(neighbor);
                        parents.add(next);
                    }
                }
            }
            out.println(num);
        }

        in.close();
        out.close();
    }

    public static void dfs(int source, int parent, int node, int current) {
        if (node == -1) {
            for (int n : videos[source].neighbors) {
                dfs(source, source, n, videos[source].distance[n]);
            }
        } else {
            videos[source].distance[node] = current;
            videos[node].distance[source] = current;
            for (int n : videos[node].neighbors) {
                if (parent == n) {
                    continue;
                }
                dfs(source, node, n, Math.min(current, videos[node].distance[n]));
            }
        }
    }

    public static class Video {
        int id;
        ArrayList<Integer> neighbors = new ArrayList<>();
        int[] distance;

        public Video(int id, int numVideos) {
            this.id = id;
            distance = new int[numVideos];
            Arrays.fill(distance, Integer.MAX_VALUE);
        }
    }
}