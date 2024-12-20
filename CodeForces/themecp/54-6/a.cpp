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

void getFactors(auto &pf, auto &primes, auto &factors, int i = 0, ll n = 1) {
	if(i == sz(pf)) {
		factors.push_back(n);
		return;
	}

	for(ll j = 0, pow = 1; j <= pf[i]; j++, pow *= primes[i])
		getFactors(pf, primes, factors, i+1, n * pow);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        map<ll, ll> freq;
        for(ll x : {a, b}){
            rep(i, 2, 1e5){
                if(x % i == 0) {
                    while(x % i == 0){
                        freq[i]++;
                        x /= i;
                    }
                }
            }
            if(x > 1) freq[x]++;
        }
        vl pws, pfs;
        for(auto [key, val] : freq) pws.pb(val), pfs.pb(key);
        pll ans = {-1, -1};
        vl fac;
        getFactors(pws, pfs, fac, 0, 1);
        for(ll x1 : fac){
            ll y1 = a * b / x1;
            ll x = (a/x1+1)*x1, y = (b/y1+1)*y1;
            if(x <= c && y <= d){
                ans = {x, y};
                break;
            }
        }
        cout << ans.f << " " << ans.s << "\n";
    }
    
    return 0;
}
