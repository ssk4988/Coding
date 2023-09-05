#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = long double;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    map<string, int> tt;
    tt["AIR"] = 0;
    tt["SEA"] = 1;
    tt["RAIL"] = 2;
    tt["TRUCK"] = 3;
    rep(cn, 0, nc){
        int n; cin >> n;
        int n4 = 4 * n;
        map<string, int> rl;
        vector<vector<pair<int, ll>>> adj(n4);
        rep(i, 0, n){
            string str; ll c; cin >> str >> c;
            rl[str] = sz(rl);
            rep(j, 0, 4){
                rep(k, 0, 4){
                    if(j == k) continue;
                    adj[i * 4 + j].pb({i * 4 + k, c});
                }
            }
        }
        int r; cin >> r;
        rep(i, 0, r){
            string str1, str2, t;ll c; cin >> str1 >> str2 >> t >> c;
            int t1 = tt[t];
            int c1 = rl[str1], c2 = rl[str2];
            adj[c1 * 4 + t1].pb({c2 * 4 + t1, c});
            adj[c2 * 4 + t1].pb({c1 * 4 + t1, c});
        }
        vi vs(n4);
        vl dist(n4, LLONG_MAX);
        int start, end;
        string ss, es; cin >> ss >> es;
        start = rl[ss], end = rl[es];
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        rep(i, 0, 4){
            dist[start * 4 + i] = 0;
            pq.push({0, start * 4 + i});
        }
        while(!pq.empty()){
            auto [d, cur] = pq.top(); pq.pop();
            if(vs[cur]) continue;
            vs[cur] = true;
            for(auto [nex, w] : adj[cur]){
                if(!vs[nex] && dist[nex] > dist[cur] + w){
                    dist[nex] = dist[cur] + w;
                    pq.push({dist[nex], nex});
                }
            }
        }
        ll ans = LLONG_MAX;
        rep(i, 0, 4){
            ans = min(ans, dist[end * 4 + i]);
        }
        cout << ans << "\n";
        
    }
}
