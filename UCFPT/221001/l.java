import java.io.*;
import java.util.*;

public class l {
    static int[] ds = { 1, 0, -1, 0 };
    static int[] da = { 0, 1, 0, -1 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        ArrayList<Integer>[] trans = new ArrayList[n * m * 4 * 2];
        ArrayList<Integer>[] cost = new ArrayList[n * m * 4 * 2]; // 0 enter 1 exit
        long[] dist = new long[n * m * 4 * 2];
        boolean[] visited = new boolean[n * m * 4 * 2];
        Arrays.fill(dist, Integer.MAX_VALUE);
        for (int i = 0; i < trans.length; i++) {
            trans[i] = new ArrayList<>();
            cost[i] = new ArrayList<>();
        }
        int[] cst = { -1, 3, 1, 2 };
        for (int s1 = 0; s1 < n; s1++) {
            for (int a1 = 0; a1 < m; a1++) {
                for (int dir = 0; dir < 4; dir++) {
                    if (s1 + ds[dir] >= 0 && s1 + ds[dir] < n && a1 + da[dir] >= 0 && a1 + da[dir] < m) {
                        for (int change = 1; change <= 3; change++) {
                            int ndir = (dir + change) % 4;
                            if (s1 + ds[ndir] >= 0 && s1 + ds[ndir] < n && a1 + da[ndir] >= 0 && a1 + da[ndir] < m) {
                                int idx1 = s1 * m * 4 * 2 + a1 * 4 * 2 + dir * 2;
                                int idx2 = (s1) * m * 4 * 2 + (a1) * 4 * 2 + ndir * 2 + 1;
                                trans[idx1].add(idx2);
                                cost[idx1].add(cst[change]);
                            }
                        }
                    }
                }
            }
        }
        tokenizer = new StringTokenizer(in.readLine());
        int sp = Integer.parseInt(tokenizer.nextToken()) - 1;
        int ap = Integer.parseInt(tokenizer.nextToken()) - 1;
        int sd = Integer.parseInt(tokenizer.nextToken()) - 1;
        int ad = Integer.parseInt(tokenizer.nextToken()) - 1;
        // FIX WRONG NEIGHBORS FOR CONSTRUCTION AND ORIGIN
        for (int i = 0; i < c; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int s1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int a1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            cst[2] = Integer.parseInt(tokenizer.nextToken());
            cst[3] = Integer.parseInt(tokenizer.nextToken());
            cst[1] = Integer.parseInt(tokenizer.nextToken());
            int pref = s1 * m * 4 * 2 + a1 * 4 * 2;
            for (int k = 0; k < 4 * 2; k++) {
                trans[pref + k] = new ArrayList<>();
                cost[pref + k] = new ArrayList<>();
            }
            for (int dir = 0; dir < 4; dir++) {
                if (s1 + ds[dir] >= 0 && s1 + ds[dir] < n && a1 + da[dir] >= 0 && a1 + da[dir] < m) {
                    for (int change = 1; change <= 3; change++) {
                        int ndir = (dir + change) % 4;
                        if (s1 + ds[ndir] >= 0 && s1 + ds[ndir] < n && a1 + da[ndir] >= 0 && a1 + da[ndir] < m) {
                            int idx1 = s1 * m * 4 * 2 + a1 * 4 * 2 + dir * 2;
                            int idx2 = (s1) * m * 4 * 2 + (a1) * 4 * 2 + ndir * 2 + 1;
                            trans[idx1].add(idx2);
                            cost[idx1].add(cst[change]);
                        }
                    }
                }
            }
        }
        cst = new int[] { -1, 0, 0, 0 };
        int pref = 0 * m * 4 * 2 + 0 * 4 * 2;
        for (int k = 0; k < 4 * 2; k++) {
            trans[pref + k] = new ArrayList<>();
            cost[pref + k] = new ArrayList<>();
        }
        for (int dir = 0; dir < 4; dir++) {
            if (0 + ds[dir] >= 0 && 0 + ds[dir] < n && 0 + da[dir] >= 0 && 0 + da[dir] < m) {
                for (int change = 1; change <= 3; change++) {
                    int ndir = (dir + change) % 4;
                    if (0 + ds[ndir] >= 0 && 0 + ds[ndir] < n && 0 + da[ndir] >= 0 && 0 + da[ndir] < m) {
                        int idx1 = 0 * m * 4 * 2 + 0 * 4 * 2 + dir * 2;
                        int idx2 = (0) * m * 4 * 2 + (0) * 4 * 2 + ndir * 2 + 1;
                        trans[idx1].add(idx2);
                        cost[idx1].add(cst[change]);
                    }
                }
            }
        }
        for (int s1 = 0; s1 < n; s1++) {
            for (int a1 = 0; a1 < m; a1++) {
                for (int dir = 0; dir < 4; dir++) {
                    int ndir = (dir + 2) % 4;
                    if (s1 + ds[dir] >= 0 && s1 + ds[dir] < n && a1 + da[dir] >= 0 && a1 + da[dir] < m)
                    //&& s1 - ds[ndir] >= 0 && s1 - ds[ndir] < n && a1 - da[ndir] >= 0 && a1 - da[ndir] < m) 
                    {
                        int idx1 = s1 * m * 4 * 2 + a1 * 4 * 2 + dir * 2 + 1;
                        int idx2 = (s1 + ds[dir]) * m * 4 * 2 + (a1 + da[dir]) * 4 * 2 + ndir * 2;
                        trans[idx1].add(idx2);
                        cost[idx1].add(1);
                    }
                }
            }
        }
        PriorityQueue<Integer> q = new PriorityQueue<>((o1, o2) -> Long.compare(dist[o1], dist[o2]));
        dist[0 * m * 4 * 2 + 0 * 4 * 2 + 0 * 2 + 1] = 0;
        dist[0 * m * 4 * 2 + 0 * 4 * 2 + 1 * 2 + 1] = 0;
        q.add(0 * m * 4 * 2 + 0 * 4 * 2 + 0 * 2 + 1);
        q.add(0 * m * 4 * 2 + 0 * 4 * 2 + 1 * 2 + 1);
        while (!q.isEmpty()) {
            int k = q.poll();
            if (visited[k])
                continue;
            visited[k] = true;
            for (int i = 0; i < trans[k].size(); i++) {
                //System.out.println(k + " " + trans[k].get(i));
                if (!visited[trans[k].get(i)] && 
                dist[trans[k].get(i)] >
                 dist[k] + cost[k].get(i)) {
                    dist[trans[k].get(i)] = dist[k] + cost[k].get(i);
                    q.add(trans[k].get(i));
                }
            }
        }
        long[] save = new long[4];
        int idxpref = sp * m * 4 * 2 + ap * 4 * 2;
        for (int i = 0; i < 4; i++) {
            save[i] = dist[idxpref + i * 4];
        }
        System.out.println(Arrays.toString(save));
        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(visited, false);
        for (int i = 0; i < 4; i++) {
            dist[idxpref + i * 4] = save[i];
            q.add(idxpref + i * 4);
        }
        while (!q.isEmpty()) {
            int k = q.poll();
            if (visited[k])
                continue;
            visited[k] = true;
            for (int i = 0; i < trans[k].size(); i++) {
                if (!visited[trans[k].get(i)] && dist[trans[k].get(i)] > dist[k] + cost[k].get(i)) {
                    dist[trans[k].get(i)] = dist[k] + cost[k].get(i);
                    q.add(trans[k].get(i));
                }
            }
        }
        idxpref = sd * m * 4 * 2 + ad * 4 * 2;
        for (int i = 0; i < 4; i++) {
            save[i] = dist[idxpref + i * 4];
        }
        System.out.println(Arrays.toString(save));
        Arrays.fill(dist, Integer.MAX_VALUE);
        Arrays.fill(visited, false);
        for (int i = 0; i < 4; i++) {
            dist[idxpref + i * 4] = save[i];
            q.add(idxpref + i * 4);
        }
        while (!q.isEmpty()) {
            int k = q.poll();
            if (visited[k])
                continue;
            visited[k] = true;
            for (int i = 0; i < trans[k].size(); i++) {
                if (!visited[trans[k].get(i)] && dist[trans[k].get(i)] > dist[k] + cost[k].get(i)) {
                    dist[trans[k].get(i)] = dist[k] + cost[k].get(i);
                    q.add(trans[k].get(i));
                }
            }
        }
        idxpref = 0 * m * 4 * 2 + 0 * 4 * 2;
        long minans = Long.MAX_VALUE;
        for (int i = 0; i < 4; i++) {
            save[i] = dist[idxpref + i * 4];
            minans = Math.min(minans, dist[idxpref + i * 4]);
        }
        System.out.println(Arrays.toString(save));
        System.out.println(minans);

        in.close();
    }
}