package solutions.snow;

import java.util.*;

public class snow {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        while(t-->0){
            int n = scan.nextInt();
            int[] h = new int[n];
            for(int i = 0;i<n;i++){
                h[i] = scan.nextInt();
            }
            char[] order = scan.next().toCharArray();
            int[] forward = new int[n];
            int[] backward = new int[n];
            for(int i = 0;i<n;i++){
                if(i==n-1){
                    forward[i] = 0;
                }else forward[i] = i+1;
                if(i==0){
                    backward[i] = n-1;
                }else{
                    backward[i] = i-1;
                }
            }
            boolean[] ded = new boolean[n];
            PriorityQueue<Node> locations = new PriorityQueue<>();

            for(int i = 0;i<n;i++){
                locations.add(new Node(i,h[i]));
            }
            int moves = 0;
            while(!locations.isEmpty()){
                Node curr = locations.poll();
                if(ded[curr.idx])continue;
                ded[curr.idx] = true;
                backward[forward[curr.idx]] = backward[curr.idx];
                forward[backward[curr.idx]] = forward[curr.idx];
                if(order[moves]=='R'){
                    int to = forward[curr.idx];
                    int count = 0;
                    while(count<curr.val-1){
                        ded[to] = true;
                        to = forward[to];
                        forward[curr.idx] = to;
                        backward[forward[curr.idx]] = backward[curr.idx];
                        forward[backward[curr.idx]] = forward[curr.idx];
                        backward[to] = backward[curr.idx];
                        count++;
                    }
                }else{
                    int to = backward[curr.idx];
                    int count = 0;
                    while(count<curr.val-1){
                        ded[to] = true;
                        to = backward[to];
                        backward[curr.idx] = to;
                        backward[forward[curr.idx]] = backward[curr.idx];
                        forward[backward[curr.idx]] = forward[curr.idx];
                        forward[to] = forward[curr.idx];
                        count++;
                    }
                }
                moves++;
            }
            System.out.println(moves);


        }
        scan.close();
    }
    static class Node implements Comparable<Node>{
        int idx, val;
        public Node(int idx, int val){
            this.idx = idx;
            this.val = val;
        }

        @Override
        public int compareTo(Node o) {
            if(o.val==this.val){
                return this.idx-o.idx;
            }
            return o.val-this.val;
        }
    }
}
