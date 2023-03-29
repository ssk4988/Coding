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
using vvl = vector<vl>;

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
vi es, ps, curp;
void onFactors(ll fact, int startinc, vl &res){
    res.pb(fact);
    if(startinc >= sz(curp)) return;
    for(int j = startinc; j < sz(curp); j++){
        curp[j]++;
        onFactors(fact * ps[j], curp[j] >= es[j] ? (j + 1) : j, res);
        curp[j]--;
    }
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;

    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n), b(n);
        vvl fsa(n);
        
        
        rep(i, 0, n){
            cin >> a[i] >> b[i];
            vector<ull> fs = factor(a[i]);
            unordered_map<int, int> ffreq;
            for(ull j : fs){
                ffreq[j]++;
            }
            ps.clear();es.clear();
            for(auto &p : ffreq){
                ps.pb(p.f);
                es.pb(p.s);
            }
            curp.clear();curp.resize(sz(es));
            onFactors(1, 0, fsa[i]);
        }
        int r = 0, l = 0;
        int ans = 0;
        ll lc = 0;
        unordered_map<ll, int> numcover;
        while(r < n){
            l = r;
            ans++;
            for(ll factor : fsa[r]){
                numcover[factor * b[r]]++;
            }
            lc = b[r++];
            while(true){
                if(r < n){
                    ll newlc = lc / gcd(lc, b[r]) * b[r];
                    bool good = false;
                    for(ll factor : fsa[r]){
                        ll prod = factor * b[r];
                        // if(prod < newlc) continue;
                        if(numcover[prod] == r - l && (prod) % newlc == 0) good = true;
                        numcover[prod]++;
                    }
                    if(!good){
                        break;
                    }
                    else{
                        lc = newlc;
                        r++;
                    }
                }
                else{
                    break;
                }
            }
            numcover.clear();
        }
        cout << ans << nL;
    }
    
    return 0;
}
