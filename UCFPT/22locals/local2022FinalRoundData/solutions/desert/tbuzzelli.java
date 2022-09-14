import java.util.*;

public class tbuzzelli {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    while (in.hasNext()) {
      int n = in.nextInt();
      long[] xs = new long[n];
      long[] ys = new long[n];
      ArrayList<Edge> allEdges = new ArrayList<>();
      for (int i = 0; i < n; i++) {
        xs[i] = in.nextLong();
        ys[i] = in.nextLong();
        for (int j = 0; j < i; j++) {
          long dx = xs[i] - xs[j];
          long dy = ys[i] - ys[j];
          Edge e = new Edge(i, j, dx * dx + dy * dy);
          allEdges.add(e);
        }
      }
      Collections.sort(allEdges, Comparator.comparingLong(e -> e.w));
      DSet ds = new DSet(n);
      BinaryLifting bl = new BinaryLifting(n);
      for (Edge e : allEdges) {
        if (ds.union(e.u, e.v)) {
          bl.add(e.u, e.v, e.w);
        }
      }
      bl.dfs();
      int q = in.nextInt();
      for (int i = 0; i < q; i++) {
        int a = in.nextInt() - 1;
        int b = in.nextInt() - 1;
        System.out.printf("%.9f\n", Math.sqrt(bl.query(a, b)));
      }
    }
  }

  static class Edge {
    int u, v;
    long w;

    Edge(int uu, int vv, long ww) {
      u = uu;
      v = vv;
      w = ww;
    }
  }

  static class DSet {
    int[] arr;

    DSet(int n) {
      Arrays.fill(arr = new int[n], -1);
    }

    int find(int a) {
      if (arr[a] < 0) return a;
      return arr[a] = find(arr[a]);
    }

    boolean union(int a, int b) {
      a = find(a);
      b = find(b);
      if (a == b) return false;
      if (arr[a] == arr[b]) arr[a]--;
      if (arr[a] <= arr[b]) arr[b] = a;
      else arr[a] = b;
      return true;
    }
  }

  static class BinaryLifting {
    ArrayList<Edge>[] adj;
    int n, logn, p[][], h[], enter[], exit[], ind;
    long vals[][];

    BinaryLifting(int n) {
      this.n = n;
      logn = (int) Math.ceil(Math.log(n) / Math.log(2));
      p = new int[n][logn];
      vals = new long[n][logn];
      h = new int[n];
      adj = new ArrayList[n];
      enter = new int[n];
      exit = new int[n];
      for (int i = 0; i < n; ++i) {
        adj[i] = new ArrayList<>();
        Arrays.fill(p[i], -1);
      }

      ind = 0;
    }

    void add(int v1, int v2, long w) {
      adj[v1].add(new Edge(v1, v2, w));
      adj[v2].add(new Edge(v2, v1, w));
    }

    void dfs() {
      dfs(0, -1, 0);
    }

    void dfs(int node, int par, long w) {
      enter[node] = ind++;
      if (par != -1) {
        p[node][0] = par;
        vals[node][0] = w;
        h[node] = h[par] + 1;
        for (int i = 1; i < logn && p[node][i - 1] != -1; ++i) {
          p[node][i] = p[p[node][i - 1]][i - 1];
          vals[node][i] = Math.max(vals[node][i - 1], vals[p[node][i - 1]][i - 1]);
        }
      } else h[node] = 0;
      for (Edge e : adj[node]) if (e.v != par) dfs(e.v, node, e.w);
      exit[node] = ind;
    }

    long query(int v1, int v2) {
      if (h[v1] < h[v2]) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
      }

      long res = 0;
      for (int i = logn - 1; i >= 0; --i)
        if (p[v1][i] != -1 && h[p[v1][i]] >= h[v2]) {
          res = Math.max(res, vals[v1][i]);
          v1 = p[v1][i];
        }

      if (v1 == v2) return res;
      for (int i = logn - 1; i >= 0; --i)
        if (p[v1][i] != p[v2][i]) {
          res = Math.max(res, vals[v1][i]);
          res = Math.max(res, vals[v2][i]);
          v1 = p[v1][i];
          v2 = p[v2][i];
        }
      return Math.max(res, Math.max(vals[v1][0], vals[v2][0]));
    }
  }
}
