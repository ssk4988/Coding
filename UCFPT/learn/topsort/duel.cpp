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
    int n, m;
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        vvi adj(n);
        vi indeg(n);
        rep(i, 0, m){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            indeg[b]++;
        }
        priority_queue<int, vi, greater<int>> pq;
        priority_queue<int> pq2;
        rep(i, 0, n){
            if(indeg[i] == 0){
                pq.push(i);
                pq2.push(i);
            }
        }
        vi indeg2(indeg);
        vi ts, ts2;
        while(!pq.empty()){
            int u = pq.top(); pq.pop();
            ts.pb(u);
            for(int v : adj[u]){
                indeg[v]--;
                if(indeg[v] == 0){
                    pq.push(v);
                }
            }
        }
        while(!pq2.empty()){
            int u = pq2.top(); pq2.pop();
            ts2.pb(u);
            for(int v : adj[u]){
                indeg2[v]--;
                if(indeg2[v] == 0){
                    pq2.push(v);
                }
            }
        }
        if(sz(ts) != n){
            cout << 0 << "\n";
        } else cout << (1 + (ts != ts2)) << "\n";
    }
    
    return 0;
}
