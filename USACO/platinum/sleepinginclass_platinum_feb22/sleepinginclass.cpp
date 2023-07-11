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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll pref = 0;
    vl prfs(n);
    rep(i, 0, n){
        ll k; cin >> k;
        pref += k;
        prfs[i] = pref;
    }
    ll sum = prfs.back();
    rep(i, 0, n){
        prfs[i] = __gcd(prfs[i], sum);
    }
    vector<ull> uf = factor(sum);
    unordered_map<ll, int> ufs;
    rep(i, 0, sz(uf)) ufs[uf[i]]++;
    vl ps;
    vi es;
    for(auto [p, e] : ufs){
        ps.pb(p);
        es.pb(e);
    }
    vl idxs;
    ll numpws = 1;
    rep(i, 0, sz(ps)){
        idxs.pb(numpws);
        numpws *= es[i] + 1;
    }
    idxs.pb(numpws);
    

    auto getidx= [&](ll v)->int{
        int res = 0;
        rep(i, 0, sz(ps)){
            while(v % ps[i] == 0){
                res += idxs[i];
                v/=ps[i];
            }
        }
        return res;
    };
    vl dp(numpws + 100);
    for(ll i : prfs){
        dp[getidx(i)]++;
    }
    rep(i, 0, sz(ps)){
        for(int j = numpws - 1; j - idxs[i] >= 0; j--){
            int idx = j - idxs[i];
            if(j / idxs[i + 1] == idx / idxs[i + 1]){
                dp[idx] += dp[j];
            }
        }
    }
    int q; cin >> q;
    rep(i, 0, q){
        ll v; cin >> v;
        if(sum % v != 0){
            cout << -1 << nL; continue;
        }
        int idx = getidx(v);
        cout << (n + sum / v - 2 * dp[idx]) << nL;
    }


    return 0;
}