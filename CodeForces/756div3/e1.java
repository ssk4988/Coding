/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class e1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        outer: for (int casenum = 0; casenum < numcases; casenum++) {
            in.readLine();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numRooms = Integer.parseInt(tokenizer.nextToken());
            int numFriends = Integer.parseInt(tokenizer.nextToken());
            int[] friends = new int[numFriends + 1];
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 0; i < numFriends; i++) {
                friends[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
            }
            friends[numFriends] = 0;
            ArrayList<Integer>[] neighbors = new ArrayList[numRooms];
            for(int i = 0; i < numRooms; i++){
                neighbors[i] = new ArrayList<>();
            }
            for (int i = 0; i < numRooms - 1; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                int r1 = Integer.parseInt(tokenizer.nextToken()) - 1;
                int r2 = Integer.parseInt(tokenizer.nextToken()) - 1;
                neighbors[r1].add(r2);
                neighbors[r2].add(r1);
            }
            int[] dist = new int[numRooms];
            Arrays.fill(dist, Integer.MAX_VALUE);
            int[] claim = new int[numRooms];
            Arrays.fill(claim, -1);
            Queue<Integer> rq = new ArrayDeque<>();
            Queue<Integer> dq = new ArrayDeque<>();
            Queue<Integer> cq = new ArrayDeque<>();
            for (int i = 0; i < friends.length; i++) {
                rq.add(friends[i]);
                dq.add(0);
                cq.add(i);
            }
            while (rq.size() > 0) {
                int room = rq.poll();
                int dis = dq.poll();
                int cla = cq.poll();
                if (dis < dist[room] || (dis == dist[room] && claim[room] == numFriends)) {
                    dist[room] = dis;
                    claim[room] = cla;
                    for (int i : neighbors[room]) {
                        if (dist[i] > dis + 1 || (dis+1 == dist[i] && claim[i] == numFriends)) {
                            rq.add(i);
                            dq.add(dis + 1);
                            cq.add(cla);
                        }
                    }
                }
            }
            for(int i = 0; i < numRooms; i++){
                if(claim[i] == numFriends && i != 0 && neighbors[i].size() == 1){
                    System.out.println("YES");
                    continue outer;
                }
            }
            System.out.println("NO");
        }
        in.close();
        out.close();
    }
}