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

ull modinverse(ll a, ll mod){
    return modpow(a, mod - 2, mod);
}
ll MOD = 1e9 + 7;
ll MOD2 = 1e9 + 7 - 1;
ll mod(ll k) {
    return k % MOD;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<pair<ll, ll>> factors(n);
    // ll numdivisors = 1, sumdivisors = 1, proddivisors = 1;
    // ll sqrtprod = 1, prod = 1;
    // bool isperfectsq = true;
    rep(i, 0, n)
    {
        cin >> factors[i].f >> factors[i].s;
        // numdivisors = mod(numdivisors * (factors[i].s + 1));
        // proddivisors = mod(proddivisors * (factors[i].s + 1), m - 1);
        // // sumdivisors = mod(sumdivisors * mod(mod(modpow(factors[i].f, factors[i].s + 1) - 1) * modinv(factors[i].f - 1)));
        // sqrtprod = mod(sqrtprod * modpow(factors[i].f, factors[i].s / 2));
        // prod = mod(prod * modpow(factors[i].f, factors[i].s));
        // isperfectsq &= factors[i].s % 2 == 0;
    }
    // cout << modinv(2, m - 1) << nL;
    // proddivisors = mod(proddivisors * modinv(2, m - 1, MOD), m - 1);
    // proddivisors = modpow(prod, proddivisors, MOD);
    // if (isperfectsq)
    //     proddivisors = mod(proddivisors * sqrtprod);
    // cout << numdivisors << " " << sumdivisors << " " << proddivisors << nL;


    ll sumdiv = 1;
    ll numdiv = 1;
    ll numdiv2 = 1;
    ll proddiv = 1;
    ll sq = 1;
    ll prod = 1;
    for(auto &p : factors){
        ll num = (modpow(p.f, p.s + 1, MOD) - 1) % MOD;
        ll denom = modinverse(p.f - 1, MOD);
        sumdiv = (sumdiv * ((num * denom) % MOD)) % MOD;
        numdiv = mod(numdiv * (p.s + 1));
        prod = mod(prod * modpow(p.f, p.s, MOD));
        if(sq != -1){
            if(p.s % 2 == 0){
                sq = mod(sq * modpow(p.f, p.s / 2, MOD));                
                numdiv2 = (numdiv2 * (p.s + 1)) % MOD2;
            }
            else{
                sq = -1;
                numdiv2 = (numdiv2 * (p.s + 1) / 2) % MOD2;
            }
        }
        else{
            numdiv2 = (numdiv2 * (p.s + 1)) % MOD2;
        }
    }
    if(sq == -1){
        proddiv = modpow(prod, numdiv2, MOD);
        
    }
    else{
        proddiv = modpow(sq, numdiv2, MOD);
    }
    cout << numdiv << " " << sumdiv << " " << proddiv << nL;

    return 0;
}