import java.io.*;
import java.util.*;

public class d {
    static int maxN = 200005;
    public static int[] p = new int[maxN];
    static ArrayList<Integer>[] c = new ArrayList[maxN];
    static TreeMap<Integer, Integer>[] cdepth = new TreeMap[maxN];
    static int n;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int i = 0; i < maxN; i++){
            c[i] = new ArrayList<>();
            cdepth[i] = new TreeMap<>();
        }
        for (int cn = 0; cn < nc; cn++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            n = Integer.parseInt(tokenizer.nextToken());
            int k = Integer.parseInt(tokenizer.nextToken());
            for (int i = 0; i < n; i++) {
                c[i].clear();
            }
            Arrays.fill(p, -1);
            tokenizer = new StringTokenizer(in.readLine());
            for (int i = 1; i < n; i++) {
                p[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                c[p[i]].add(i);
            }
            int low = 1;
            int high = 200005;
            while (low < high) {
                int mid = low + (high - low) / 2;
                for (int i = 0; i < n; i++) {
                    cdepth[i].clear();
                }
                int kcnt = dfscnt(0, mid);
                if (kcnt <= k) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            b.append(low + "\n");
        }
        System.out.print(b);
        in.close();
    }

    static int dfscnt(int cur, int k) {
        if (k == 1) {
            return n - 1 - c[0].size();
        }
        int ans = 0;

        for (int i : c[cur]) {
            ans += dfscnt(i, k);
        }

        // up[cur]>k
        if (cur != 0 && p[cur] != 0) {
            if (cdepth[cur].size() > 0 && cdepth[cur].lastKey() >= k - 2)
                ans++;
            else {
                int down = cdepth[cur].size() > 0 ? cdepth[cur].lastKey() + 1 : 0;
                if (!cdepth[p[cur]].containsKey(down)) {
                    cdepth[p[cur]].put(down, 0);
                }
                cdepth[p[cur]].put(down, cdepth[p[cur]].get(down) + 1);
            }
        }
        return ans;
    }
}