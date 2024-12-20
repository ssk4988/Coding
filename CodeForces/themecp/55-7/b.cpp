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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vvi sm(n+2);
        sm[0].pb(0);
        vvi a(n+5, vi(n+5));
        rep(i, 1, n+1){
            rep(j, i, n+1){
                cin >> a[i][j];
            }
        }
        rep(i, 1, n+2){
            priority_queue<pii> pq;
            vi pnt(i);
            rep(j, 0, i) {
                pq.push({a[j+1][i-1] + sm[j][pnt[j]], j});
            }
            int times = k;
            while(times > 0 && sz(pq)){
                auto [v_u, u] = pq.top(); pq.pop();
                sm[i].pb(v_u);
                pnt[u]++;
                if(pnt[u] < sz(sm[u])) pq.push({a[u+1][i-1] + sm[u][pnt[u]], u});
                times--;
            }
        }
        assert(sz(sm[n+1]) == k);
        for(int v : sm[n+1]) cout << v << " ";
        cout << "\n";
    }
    
    return 0;
}
