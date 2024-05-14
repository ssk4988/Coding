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
const int oo = 1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> w(n);
    rep(i, 0, n){
        cin >> w[i];
    }
    int l = sz(w[0]);
    auto dif = [&](string &a, string &b) -> vi {
        vi d;
        rep(i,0,l) if(a[i] != b[i]) d.pb(i);
        return d;
    };
    vvi adj(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(sz(dif(w[i], w[j])) == 1) adj[i].pb(j);
        }
    }
    auto bfs = [&](int s) -> vi {
        vi d(n, oo);
        queue<pii> q;
        q.push({0, s});
        while(!q.empty()){
            auto [d_u, u] = q.front(); q.pop();
            if(d[u] != oo) continue;
            d[u] = d_u;
            for(int v : adj[u]){
                q.push({d_u + 1, v});
            }
        }
        return d;
    };
    vi fromsource = bfs(0), fromsink = bfs(1);
    int best = fromsource[1];
    vector<string> ws;
    rep(i, 0, n){
        rep(j, 0, n){
            vi d = dif(w[i], w[j]);
            if(sz(d) != 2) continue;
            string w1 = w[i], w2 = w[i];
            w1[d[0]] = w[j][d[0]];
            w2[d[1]] = w[j][d[1]];
            int dist = fromsource[i] + 1 + 1 + fromsink[j];
            if(dist < best){
                best = dist;
                ws = {w1, w2};
            } else if(dist == best) {
                ws.push_back(w1);
                ws.push_back(w2);
            }
        }
    }
    if(best == fromsource[1]) cout << 0 << "\n";
    else cout << *min_element(all(ws)) << "\n";
    if(best == oo) best = -1;
    cout << best << "\n";
    
    return 0;
}
