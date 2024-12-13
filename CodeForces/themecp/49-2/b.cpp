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
    rep(cn, 0, nc){
        int n, m, k; cin >> n >> m >> k;
        vector<array<int, 3>> p(k);
        rep(i, 0, k){
            cin >> p[i][1] >> p[i][0];
            p[i][1] *= -1;
            p[i][2] = i;
        }
        sort(all(p));
        vi use(k);
        ll ans = 0;
        int mxr = 0, mxc = 0;
        for(auto [c, r, i] : p) {
            r *= -1;
            if(r <= mxr) continue;
            use[i] = 1;
            ans += ll(r) * (m+1 - c);
            ans -= ll(mxr) * (m+1-c);
            mxr = r;
            mxc = c;
        }
        ans = ll(n) * m - ans;
        cout << ans << "\n";
        rep(i, 0, k){
            cout << use[i] << " ";
        }
        cout << "\n";
    }    
    
    return 0;
}
