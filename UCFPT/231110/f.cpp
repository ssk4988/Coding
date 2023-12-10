#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<ll, ll>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> m >> n;
        vector<vii> adj(n);
        vector<vector<int>> cs(m, vi(3));
        rep(j, 0, 3){
            rep(i, 0, m){
                cin >> cs[i][j];
            }
        }
        rep(i, 0, m){
            cs[i][0]--, cs[i][1]--;
            adj[cs[i][1]].push_back({cs[i][0], cs[i][2]});
        }
        const ll BAD = 1e18;
        vector<ll> dist(n, BAD);
        priority_queue<pii, vii, greater<pii>> pq;
        vi t(n);
        rep(i, 0, n){
            cin >> t[i];
            if(t[i] == 0){
                dist[i] = 0;
                pq.push({dist[i], i});
            }
        }
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(d > dist[u]) continue;
            for(auto [v, w] : adj[u]){
                if(dist[v] > d + w){
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        bool works = true;
        ll cost = 0;
        rep(i, 0, n){
            if(t[i] == 2){
                if(dist[i] == BAD){
                    works = false;
                    break;
                }
                cost += dist[i];
            }
        }
        cout << "Case #" << (cn + 1) << ": " << (works ? cost : -1) << "\n";
    }
    return 0;
}
