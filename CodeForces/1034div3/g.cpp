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
    const int LIM = 5e5+10;
    
    vvi divts(LIM);
    rep(i, 1, LIM) {
        for(int j = i; j < LIM; j += i) divts[j].pb(i);
    }
    rep(cn, 0, nc) {
        int n, m, q; cin >> n >> m >> q;
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        vi divs = divts[m];
        vi ans(sz(divs));
        rep(i, 0, n-1) {
            rep(j, 0, sz(divs)) if((a[i] % divs[j]) > (a[i+1] % divs[j])) ans[j]++;
        }
        rep(qid, 0, q) {
            int t; cin >> t;
            if(t == 1){
                int i, x; cin >> i >> x; i--;
                rep(j, 0, sz(divs)) {
                    if(i && (a[i-1] % divs[j]) > (a[i] % divs[j])) ans[j]--;
                    if(i+1 < n && (a[i] % divs[j]) > (a[i+1] % divs[j])) ans[j]--;
                }
                a[i] = x;
                rep(j, 0, sz(divs)) {
                    if(i && (a[i-1] % divs[j]) > (a[i] % divs[j])) ans[j]++;
                    if(i+1 < n && (a[i] % divs[j]) > (a[i+1] % divs[j])) ans[j]++;
                }
            } else {
                int k; cin >> k;
                k = gcd(k, m);
                int idx = lower_bound(all(divs), k) - begin(divs);
                cout << (ans[idx] < m / divs[idx] ? "YES" : "NO") << "\n";
            }
        }
    }
    
    return 0;
}
