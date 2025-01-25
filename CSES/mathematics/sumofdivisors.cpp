#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"


const ll mod = 1e9+7;
const int inv2 = (mod+1)/2;
ll nc2(ll n) {
	n %= mod;
	return n * (n+1) % mod * inv2 % mod;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

	ll n; cin >> n;
	ll ans = 0;
	vl div_low, div_high;
	for(ll i = 1; i * i <= n; i++) {
		div_low.push_back(i);
		if(i * i != n) {
			div_high.push_back(n / i);
		}
	}
	vl divs;
	reverse(all(div_high));
	divs.insert(end(divs), all(div_low));
	divs.insert(end(divs), all(div_high));
	ll prv = 0;
	for(ll d : divs) {
		ll other = n / d;
		ll sm = nc2(d) - nc2(prv);
		sm %= mod;
		sm += mod;
		sm %= mod;
		prv = d;
		(ans += sm * other) %= mod;
	}
	cout << ans << "\n";
    return 0;
}
