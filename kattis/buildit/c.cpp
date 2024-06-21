#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vi t{k, n - k};
    string ts = "NS";
    int mxt = n - k > k;
    vvi adj(n);
    vi c(n);
    rep(i, 0, n) cin >> c[i];
    vii ed;
    rep(i, 0, m){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
        ed.pb({u, v});
        ed.pb({v, u});
    }
    if(t[mxt] == n){
        rep(i, 0, n){
            cout << ts[mxt];
        }
        cout << "\n";
        return 0;
    }
    auto dijk = [&](int source) -> vi {
        vi dist(n, -1);
        priority_queue<pii, vii, greater<pii>> pq;
        pq.push({c[source], source});
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(dist[u] != -1) continue;
            dist[u] = d;
            for(int v : adj[u]){
                pq.push({d + c[v], v});
            }
        }
        return dist;
    };
    vi dsource = dijk(0), dsink = dijk(n-1);
    rep(i, 0, n) adj[i].clear();
    vi adjt(n);
    for(auto [u, v] : ed){
        if(dsource[u] + dsink[v] == dsource[n-1]){
            adj[u].pb(v);
            if(u == 0) adjt[v] |= 1;
            if(v == n-1) adjt[u] |= 2;
        }
    }
    vi cnt(4);
    rep(i, 0, n) cnt[adjt[i]]++;
    int mnt = cnt[2] < cnt[1] ? 2 : 1;
    if(1 + cnt[mnt] > t[mxt]){
        cout << "impossible\n";
        return 0;
    }
    // rep(i, 0, n) cout << adjt[i] << " ";
    // cout << "\n";
    // cout << mnt << " " << cnt[mnt] << "\n";
    vi res(n, -1);
    res[mnt == 2 ? n-1 : 0] = mxt;
    t[mxt]--;
    if(!(adjt[mnt == 2 ? n-1 : 0] & (3 - mnt))){
        // cout << "fill different\n";
        res[mnt == 2 ? 0 : n-1] = 1-mxt;
        t[1-mxt]--;
    }
    rep(i, 0, n){
        if(res[i] != -1) continue;
        if(adjt[i] == mnt){
            // cout << "assign " << i << " " << mxt << "\n";
            res[i] = mxt;
            t[mxt]--;
        }
    }
    rep(i, 0, n){
        if(res[i] != -1) continue;
        bool done = false;
        rep(j, 0, 2){
            if(t[j]){
                t[j]--;
                res[i] = j;
                done = true;
                break;
            }
        }
        assert(done);
    }
    rep(i, 0, n){
        cout << ts[res[i]];
    }
    cout << "\n";

    
    return 0;
}
