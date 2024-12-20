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
        ll L, R; cin >> L >> R;
        ll ans = 0;
        if(R/2 >= L){
            ans += R/2-L+1;
        }
        vl targets, btargets;
        for(int i = 1; i * i <= L-1; i++) {
            targets.pb(i);
            if((L-1)/i > i) btargets.pb((L-1)/i);
        }
        reverse(all(btargets));
        targets.insert(end(targets), all(btargets));
        for(ll t : targets) {
            ll s = (L-1) / (t+1) +1, e = (L-1) / t + 1;
            ll v = t + 2;
            // smallest x such that x * v > r as a limiter
            // x > r / v
            // x >= (r+1) / v
            e = min(e, R / v + 1);
            e = min(e, L);
            e = max(e, s);
            ans += e-s;
        }
        cout << ans << "\n";
    }    
    
    return 0;
}
