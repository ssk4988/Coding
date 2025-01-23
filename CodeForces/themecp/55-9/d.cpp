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
    int n; ll k; cin >> n >> k;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    
    ll ans = 0;
    rep(_, 0, n) {
        ll cur = 0;
        ll mx = 0;

        vl pref(a);
        partial_sum(all(pref), begin(pref));
        pref.insert(begin(pref), 0);
        vl cnt0(n);
        rep(i, 0 ,n) cnt0[i] = a[i] == 0;
        vl pref0(cnt0);
        partial_sum(all(pref0), begin(pref0));
        pref0.insert(begin(pref0), 0); 
        if(pref0.back() * k < abs(pref.back())){
            cout << -1 << "\n";
            return 0;
        }
        rep(i, 0, n) {
            if(a[i] != 0){
                cur += a[i];
                mx = max(mx, cur);
                continue;
            }
            int left = pref0.back() - pref0[i+1];
            ll rem = pref.back() - pref[i+1];
            ll rem_cur = cur + rem;
            cur += min(k, left * k - rem_cur);
            mx = max(mx, cur);
        }
        ans = max(ans, mx+1);
        rotate(begin(a), begin(a)+1, end(a));
    }
    cout << ans << "\n";


    return 0;
}
