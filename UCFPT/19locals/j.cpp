#include <bits/stdc++.h>
using namespace std;

// using ld = long double;
using ld = double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

const int N = 1000;
using mat = array<array<ld, N>, N>;

mat operator*(mat &a, mat &b) {
    mat res{};
    rep(i, 0, N){
        rep(j, 0, N){
            rep(k, 0, N){
                // if(k == i && j != i) continue;
                res[i][j] += a[i][k] * a[k][j];
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    mat base{};
    vector<vector<pair<int, ld>>> adj(n);
    vi lolly(n);
    rep(i, 0, n){
        cin >> lolly[i];
        int k; cin >> k;
        rep(j, 0, k){
            int to; ld w; cin >> to >> w; to--;
            if(to < n){
                base[i][to] += w;
            } else {
                adj[i].push_back({to, w});
                base[i][N/2 + i] += w;
            }
        }
    }
    rep(i, N/2, N) base[i][i] = 1;
    rep(i, 0, 5){
        base = base * base;
    }
    vector<ld> res(m);
    vector<ld> stay(m);
    rep(i, 0, n){
        rep(j, 0, n){
            stay[j] += lolly[i] * base[i][j+N/2];
        }
    }
    rep(i, 0, n){
        if(sz(adj[i]) == 0) continue;
        ld sum = 0;
        for(auto [to, w] : adj[i]){
            sum += w;
        }
        for(auto [to, w] : adj[i]){
            stay[to] += w / sum * stay[i];
        }
    }
    cout << fixed << setprecision(8);
    // rep(i, 0, n){
    //     cout << stay[i] << "\n";
    // }
    // cout << "actual: \n";
    rep(i, 0, m){
        if(i < n) cout << 0 << "\n";
        else cout << stay[i] << "\n";
    }

    return 0;
}
