import java.io.*;
import java.util.*;

public class b {
    static int n;
    static int[] child;
    static ArrayList<Integer>[] parent;
    static boolean[] solved;
    static boolean[] visited;
    static int[] inCycle;
    static long ways = 0;
    static int[] a;
    static ArrayList<HashSet<Integer>> cycles = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        a = new int[n];
        child = new int[n];
        solved = new boolean[n];
        visited = new boolean[n];
        inCycle = new int[n];
        Arrays.fill(inCycle, -1);
        parent = new ArrayList[n];
        for (int i = 0; i < parent.length; i++) {
            parent[i] = new ArrayList<>();
        }
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(tokenizer.nextToken());
            int c = i + a[i];
            if (c < 0 || c >= n)
                c = -1;
            child[i] = c;
            if (child[i] != -1)
                parent[child[i]].add(i);
        }

        for (int i = 0; i < n; i++) {
            if (visited[i])
                continue; // not necessary
            findCycle(i);
        }
        visited = new boolean[n];
        HashSet<Integer> mset = new HashSet<>();
        for (int i = 0; i < cycles.size(); i++) {
            mset.clear();
            for (int k : cycles.get(i)) {
                mset.add(a[k]);
            }
            for (int k : cycles.get(i)) {
                dfsBack(k, mset);
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (child[i] == -1) {
                mset.clear();
                mset.add(a[i]);
                dfsBack(i, mset);
            }
        }
        System.out.println(ways);
        in.close();
    }

    static void dfsBack(int cur, HashSet<Integer> mset) {
        if (visited[cur])
            return;
        visited[cur] = true;
        ways += mset.size();
        for (int p : parent[cur]) {
            boolean contains = mset.contains(a[p]);
            if (!contains) {
                mset.add(a[p]);
            }
            dfsBack(p, mset);
            if (!contains) {
                mset.remove(a[p]);
            }
        }
    }

    static void genCycle(int start) {
        int id = cycles.size();
        cycles.add(new HashSet<>());
        ArrayDeque<Integer> q = new ArrayDeque<>();
        q.add(start);
        while (!q.isEmpty()) {
            int k = q.poll();
            inCycle[k] = id;
            cycles.get(id).add(k);
            if (inCycle[child[k]] == -1) { // never checked if child not -1
                q.add(child[k]);
            }
        }
    }

    static void findCycle(int start) {
        ArrayDeque<Integer> q = new ArrayDeque<>();
        q.add(start);
        HashSet<Integer> thiscall = new HashSet<>();
        while (!q.isEmpty()) {
            int k = q.poll();
            if (visited[k])
                continue;
            visited[k] = true;
            thiscall.add(k);
            if (child[k] != -1) {
                if (thiscall.contains(child[k])) {
                    if (inCycle[child[k]] == -1) {
                        // in cycle
                        genCycle(k);
                    } else {
                        // not in cycle
                        // shouldn't be called
                        break;
                    }
                } else {
                    q.add(child[k]);
                }
            }
        }
    }
}