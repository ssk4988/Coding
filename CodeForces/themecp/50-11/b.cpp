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
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	auto f = [&](ull x) { return modmul(x, x, n) + i; };
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

using int128 = __int128_t;

int128 nc2(ll n) {
    return int128(n) * (n-1) / 2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll n; cin >> n;
        if(n % 2 == 1) {
            cout << 2 << "\n";
            continue;
        }
        ll nrem = 1;
        while(n % (nrem * 2) == 0) nrem *= 2;
        bool works = false;
        if(!works) {
            ll k = nrem * 2;
            if(nc2(k) < n && (n - nc2(k)) % k == 0){
                works = true;
                cout << k << "\n";
                continue;
            }
        }
        ll k = n / nrem;
        if(k > 1 && nc2(k) < n && (n - nc2(k)) % k == 0){
            works = true;
            cout << k << "\n";
            continue;
        }
        // cout << "-1\n";
        // continue;
        // auto v = factor(n / nrem);
        // if(sz(v) == 1) {
        //     cout << "-1\n";
        //     continue;
        // }
        // bool works = false;
        

        // for(ull x : v){
        //     if(x&1) {
        //         // nrem /= x;
        //         if(n <= nc2(x)) continue;
        //         // assert(n >= x * (x-1) / 2);
        //         // assert((n - x * (x-1) / 2) % x == 0);
        //         if((n - nc2(x)) % x != 0) continue;
        //         works = true;
        //         cout << x << "\n";
        //         break;
        //     }
        // }
        if(!works) cout << -1 << "\n";
    }
    
    return 0;
}