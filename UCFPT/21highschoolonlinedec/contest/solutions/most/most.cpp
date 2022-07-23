// 2021 UCF HSPT Online - Minimum Odd Spanning Tree
// Author: Billy Quiroga
#include <bits/stdc++.h>
 
using namespace std;

struct DSU {
  vector<int> p;
  DSU(int n) {
    p = vector<int>(n);
    iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if(a != b) {
      p[a] = b;
      return true;
    }
    return false;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;

  typedef array<int, 3> edge;
  vector<edge> es;

  for(int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    es.push_back({u, v, w});
  }

  sort(es.begin(), es.end(),
  [&](edge a, edge b) -> bool {
    return a[2] < b[2];
  });

  DSU dsu(n);
  long long mst = 0;

  vector<bool> in_mst(m);
  vector<vector<pair<int, int>>> adj(n);
  
  for(int i = 0; i < m; i++) {
    auto [u, v, w] = es[i];
    if(dsu.join(u, v)) {
      mst += w;
      in_mst[i] = true;
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }
  }

  if(mst & 1) {
    cout << mst << '\n';
    return;
  }

  int lg = 32 - __builtin_clz(n);
  vector<vector<int>> L, O, E;
  L = O = E = vector<vector<int>>(lg, vector<int>(n, -1));
  vector<int> d(n);

  function<void(int, int)> create_lift_table =
  [&](int u, int p) {
    for(int k = 0; k < lg - 1; k++) {
      if(L[k][u] == -1) continue;
      L[k + 1][u] = L[k][L[k][u]];
      O[k + 1][u] = max(O[k][u], O[k][L[k][u]]);
      E[k + 1][u] = max(E[k][u], E[k][L[k][u]]);
    }
    for(auto [v, w] : adj[u]) {
      if(v == p) continue;

      L[0][v] = u;
      d[v] = d[u] + 1;
      if(w & 1) O[0][v] = w;
      else E[0][v] = w;

      create_lift_table(v, u);
    }
  };

  create_lift_table(0, -1);
  
  function<int(int, int)> walk =
  [&](int u, int x) {
    for(int k = lg - 1; k >= 0; k--)
      if(x & (1 << k))
        u = L[k][u];
    return u;
  };

  function<int(int, int)> lca =
  [&](int u, int v) {
    if(d[u] < d[v]) swap(u, v);
    u = walk(u, d[u] - d[v]);
    if(u == v) return u;
    for(int k = lg - 1; k >= 0; k--) {
      if(L[k][u] == L[k][v]) continue;
      tie(u, v) = tie(L[k][u], L[k][v]);
    }
    return L[0][u];
  };

  function<int(int, int, vector<vector<int>>&)> max_on_path =
  [&](int u, int v, vector<vector<int>>& X) {
    int l = lca(u, v);
    int max_edge = -1;
    int du = d[u] - d[l], dv = d[v] - d[l];
    for(int k = lg - 1; k >= 0; k--) {
      if(du & (1 << k)) {
        max_edge = max(max_edge, X[k][u]);
        u = L[k][u];
      }
      if(dv & (1 << k)) {
        max_edge = max(max_edge, X[k][v]);
        v = L[k][v];
      }
    }
    return max_edge;
  };

  long long most = (long long) 1e18;

  for(int i = 0; i < m; i++) {
    if(in_mst[i]) continue;

    auto [u, v, w] = es[i];
    int to_remove = -1;
    if(w & 1) to_remove = max_on_path(u, v, E);
    else to_remove = max_on_path(u, v, O);

    if(to_remove == -1) continue;

    most = min(most, mst - to_remove + w);
  }

  if(most == (long long) 1e18) cout << "-1\n";
  else cout << most << '\n';
}

int main() {
  int t;
  cin >> t;
  for(int tc = 1; tc <= t; tc++) solve();
  return 0;
}
