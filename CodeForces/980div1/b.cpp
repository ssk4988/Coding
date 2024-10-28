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
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vl pref(a);
        partial_sum(all(pref), begin(pref));
        vi b(n);
        rep(i,0,n){
            cin >> b[i]; b[i]--;
        }
        vi mx(b);
        rep(i, 1, n) mx[i] = max(mx[i], mx[i-1]);
        ll best = 0;
        priority_queue<pll, vll, greater<>> pq;
        pq.push({0, 0});
        vl d(n, -1);
        while(sz(pq)){
            auto [d_u, u] = pq.top(); pq.pop();
            if(d[u] != -1) continue;
            d[u] = d_u;
            best = max(best, pref[u] - d_u);
            if(u) pq.push({d_u, u-1});
            pq.push({d_u + a[u], b[u]});
        }
        cout << best << "\n";
    }
    
    return 0;
}
