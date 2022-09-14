import java.io.*;
import java.util.*;

public class wordtree {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());

        int n = Integer.parseInt(tokenizer.nextToken());
        int len = Integer.parseInt(tokenizer.nextToken());
        int[][] d = new int[n][len];
        for (int i = 0; i < n; i++) {
            String s = in.readLine();
            for (int j = 0; j < len; j++) {
                d[i][j] = s.charAt(j) - 'A';
            }
        }
        int[][] adj = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int c = 0;
                for (int k = 0; k < len; k++) {
                    c += Math.abs(d[i][k] - d[j][k]);
                }
                adj[i][j] = c;
            }
        }
        int low = 0;
        int high = 1000000000;
        while(low < high){
            int mid = low + (high - low)/2;
            boolean[] v =new boolean[n];
            ArrayDeque<Integer> q = new ArrayDeque<>();
            q.add(0);
            while(!q.isEmpty()){
                int k = q.poll();
                if(v[k])continue;
                v[k] = true;
                for(int i = 0 ; i < n; i ++){
                    if(!v[i] && adj[i][k] <= mid){
                        q.add(i);
                    }
                }
            }
            boolean works = true;
            for(int i = 0; i < n; i++){
                works &= v[i];
            }
            if(works){
                high = mid;
            }
            else{
                low = mid + 1;
            }
        }
        System.out.println(low);
    }

    public static class p implements Comparable<p> {
        int i;
        int c = 1000000000;
        boolean done = false;

        @Override
        public int compareTo(wordtree.p o) {
            return c - o.c;
        }
    }
}