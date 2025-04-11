#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi &B) {
    if(A[a] != L) return 0;
    A[a] = -1;
    for(int b : g[a]) if(B[b] == L+1) { 
        B[b] = 0;
        if(btoa[b] == -1 || dfs(btoa[b], L+1, g, btoa, A, B))
            return btoa[b]=a, 1;
    }
    return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
    int res = 0;
    vi A(g.size()), B(btoa.size()), cur, next;
    for(;;) {
        fill(all(A), 0);
        fill(all(B), 0);
        cur.clear();
        for(int a : btoa) if(a != -1) A[a] = -1;
        rep(a, 0, sz(g)) if(A[a] == 0) cur.push_back(a);
        for(int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for(int a : cur) for(int b : g[a]) {
                if(btoa[b] == -1) {
                    B[b] = lay;
                    islast = 1;
                } else if(btoa[b] != a && !B[b]) {
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if(islast) break;
            if(next.empty()) return res;
            for(int a : next) A[a] = lay;
            cur.swap(next);
        }
        rep(a, 0, sz(g))
            res += dfs(a, 0, g, btoa, A, B);
    }
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    vi btoa(m, -1);
    vvi g(n);
    rep(i, 0,n) {
        cin >> grid[i];
        rep(j, 0, m) {
            if(grid[i][j] == 'X') {
                g[i].push_back(j);
            }
        }
    }
    int flow = hopcroftKarp(g, btoa);
    cout << flow << "\n";
    // rep(i, 0, sz(btoa)){
    //     cerr << i/m << " " << i%m << " " << btoa[i] << endl;
    // }

    return 0;
}
