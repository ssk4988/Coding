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

#define bitat(x, b) (((x) >> (b)) & 1)

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
const int B = 60;
struct XORBasis {
	ll basis[B];
    XORBasis() {
        memset(basis, 0, sizeof basis);
    }
	int npivot = 0, nfree = 0;
	bool check(ll v) {
		rep(i, 0, B)
			if (bitat(v, i)) v ^= basis[i];
		return v == 0;
	}
	bool add(ll v) {
		rep(i, 0, B)
			if (bitat(v, i)) {
				if (basis[i] == 0) {
                    basis[i] = v, ++npivot;
                    return true;
                }
				v ^= basis[i];
			}
        return !++nfree;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {

        ll c, d; cin >> c >> d; d++;
        XORBasis b;
        if(c <= 2 && 3 <= d) b.add(2);
        auto go = [&](ll l, ll r, int depth, auto &&go) -> void {
            if(d <= l || r <= c) return;
            ll m = l + (r-l)/2;
            if(c <= l && r <= d) {
                // cout << l << "," << r << " depth " << depth << " lowest " << b.lowestempty << " in " << c << "," << d << endl;
                if(r-l == 1) {
                    if(isPrime(l)) b.add(l);
                    return;
                }
                if(depth > 14) {
                    b.add(l);
                    rep(i, 1, depth) {
                        ll x = l + (1LL << i) + 1;
                        if(x < r) b.add(x);
                    }
                    return;
                }
                for(ll i = l; i < r; i++) {
                    if(isPrime(i)) b.add(i);
                }
                return;
            } else {
                go(l, m, depth-1, go);
                go(m, r, depth-1, go);
            }
        };
        go(0, 1LL << 60, 60, go);
        cout << (1LL << b.npivot) << "\n";
    }
    
    return 0;
}
