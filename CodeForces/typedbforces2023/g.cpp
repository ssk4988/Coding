#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

using t3 = tuple<int, int, int>;

// bool cmp3(t3 a, t3 b){
//     if(a.f == b.f) return a.s > b.s;
//     return a.f < b.f;
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi validc(n, 1), heights(n), rootc(n, -1), colorabove(n, -1), weights(n), blocked(n);
    vector<vector<tuple<int, int, int>>> adj(n); // b, w, c
    vector<map<int, int>> occ(n);
    rep(i, 0, n - 1){
        int u, v, w, c; cin >> u >> v >> w >> c; u--, v--, c--;
        adj[u].pb({v, w, c});
        adj[v].pb({u, w, c});
    }
    auto dfs = [&](int cur, int par, int d, int col, auto &&dfs)->void{
        heights[cur] = d;
        colorabove[cur] = col;
        for(auto [nex, w, c] : adj[cur]){
            if(nex == par) continue;
            if(rootc[c] == -1 || heights[rootc[c]] > heights[cur]){
                rootc[c] = cur;
            }
            occ[cur][c]++;
            occ[nex][c]++;
            weights[c] += w;
            dfs(nex, cur, d + 1, c, dfs);
        }
    };
    dfs(0, -1, 0, -1, dfs);
    vi adj1color(n);
    rep(i, 0, n){
        for(auto [color, freq] : occ[i]){
            if(freq == 1) adj1color[color]++;
            if(freq > 2) validc[color] = false;
        }
    }
    rep(i, 0, n){
        if(adj1color[i] > 2 || weights[i] == 0) validc[i] = false;
        // if(validc[i]){
        //     cout << (i + 1) << " is a valid color\n";
        // }
    }
    // best color that has rootc here
    // blocked, -weights, color
    vector<multiset<t3>> buckets(n);
    rep(i, 0, n){
        if(!validc[i]) continue;
        buckets[rootc[i]].insert({0, -weights[i], i});
        // cout << i << " " << weights[i] << " " << rootc[i] << nL;
    }
    // stores best guys from each bucket
    // blocked, -weights, bucket
    multiset<t3> best;
    rep(i, 0, n){
        if(sz(buckets[i]) == 0) continue;
        auto [bl, negw, color] = *buckets[i].begin();
        best.insert({bl, negw, i});
    }
    vi lzadd(n);
    rep(i, 0, q){
        int t, v; cin >> t >> v;
        v--;
        // cout << "query " << i << ":\n";
        if(buckets[v].size()){
            auto [bl, negw, color] = *buckets[v].begin();
            // cout << bl << " " << negw << " " << color << nL;
            best.erase(best.find({bl + lzadd[v], negw, v}));
        }
        if(t == 0) lzadd[v]++;
        else lzadd[v]--;
        if(buckets[v].size()){
            auto [bl, negw, color] = *buckets[v].begin();
            // cout << bl << " " << negw << " " << color << nL;
            best.insert({bl + lzadd[v], negw, v});
        }
        // cout << lzadd[v] << nL;
        if(colorabove[v] != -1){
            int c = colorabove[v];
            int r = rootc[c];
            if(validc[c]){
                // cout << "color above: " << c << " bucket above: " << r << nL;
                auto [bl1, negw1, color1] = *buckets[r].begin();
                // cout << bl1 << " " << -negw1 << " " << color1 << nL;
                best.erase(best.find({bl1 + lzadd[r], negw1, r}));
                buckets[r].erase(buckets[r].find({blocked[c], -weights[c], c}));
                if(t == 0) blocked[c]++;
                else blocked[c]--;
                // cout << blocked[c] << nL;
                buckets[r].insert({blocked[c], -weights[c], c});
                auto [bl2, negw2, color2] = *buckets[r].begin();
                // cout << bl2 << " " << -negw2 << " " << color2 << nL;
                best.insert({bl2 + lzadd[r], negw2, r});
            }
        }
        auto [bl1, negw1, color1] = *best.begin();
        cout << (bl1 == 0 ? -negw1 : 0) << nL;
    }
    
    return 0;
}
