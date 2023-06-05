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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

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
vi curp, es, res;
vector<int> ps;
void onFactors(int cur, int idx){
    if(idx == sz(curp)) return;
    for(int i = idx; i < sz(curp); i++){
        curp[i]++;
        res.pb(cur * ps[i]);
        onFactors(cur * ps[i], i + (curp[i] >= es[i]));
        curp[i]--;
    }
}

vi genFactors(int n){
    vector<ull> fs = factor(n);
    unordered_map<int, int, custom_hash> ffreq;
    for(ull j : fs){
        ffreq[int(j)]++;
    }
    es.clear();
    ps.clear();
    res.clear();
    for(auto &p : ffreq){
        ps.pb(p.f);
        es.pb(p.s);
    }
    curp = vi(sz(es));
    onFactors(1, 0);
    return vi(res);
}

bool DEBUG = true;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    unordered_map<int, vi, custom_hash> fs;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi a(n);
        unordered_map<int, ll, custom_hash> freq;
        rep(i, 0, n)
        {
            cin >> a[i];
            freq[a[i]]++;
            if(fs.count(a[i]) == 0) fs[a[i]] = genFactors(a[i]);
        }
        ll ans = 0;
        for(auto &p : freq){
            auto [i, f] = p;
            if(f > 2){
                ans += f * (f - 1) * (f - 2);
            }
            for(int j : fs[i]){
                if((i / j) % j == 0 && freq.count(i / j) && freq.count(i / j / j)){
                    ans += f * freq[i / j] * freq[i / j / j];
                }
            }
        }
        cout << ans << nL;
    }

    return 0;
}
