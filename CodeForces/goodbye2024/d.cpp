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

const ll mod = 998244353;
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
void solve() {
    int n, q; cin >> n >> q;
    vl a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    vl as(a), bs(b);
    sort(all(as)), sort(all(bs));
    ll ans = 1;
    rep(i, 0, n) (ans *= min(as[i], bs[i])) %= mod;
    cout << ans << " ";
    rep(i, 0, q){
        int o, x; cin >> o >> x; x--;
        if(o == 1) {
            ll v = a[x];
            int idx = upper_bound(all(as), v)-begin(as);
            idx--;
            (ans *= modpow(min(as[idx], bs[idx]), mod-2)) %= mod;
            as[idx]++;
            a[x]++;
            (ans *= min(as[idx], bs[idx])) %= mod;
        } else {
            ll v = b[x];
            int idx = upper_bound(all(bs), v)-begin(bs);
            idx--;
            (ans *= modpow(min(as[idx], bs[idx]), mod-2)) %= mod;
            bs[idx]++;
            b[x]++;
            (ans *= min(as[idx], bs[idx])) %= mod;
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
