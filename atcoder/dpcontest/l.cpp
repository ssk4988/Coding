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

const int LIM = 1000000;
vi lp(LIM+1), primes;
const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; (b *= b) %= mod, e /= 2)
        if(e&1) (res *= b) %= mod;
    return res;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    rep(i, 2, LIM + 1) {
        if (lp[i] == 0) primes.push_back(lp[i] = i);
        for (int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    int n; cin >> n;
    vi a(n);
    vi par(n+1);
    rep(i, 2, n+1) par[i] = 1 ^ par[i / lp[i]];
    vvi div(n+1);
    vi mob(n+1);
    vl frac(n+1);
    mob[1] = 1;
    rep(i, 1, n+1) {
        ll term = modpow(i, mod-2);
        // cerr << "term for " << i << " is " << term << endl;
        for(int j = i; j <= n; j += i) {
            div[j].push_back(i);
            // (frac[j] += term * mob[j/i]) %= mod;
            // if(par[j/i]) (frac[j] -= term) %= mod;
            // else (frac[j] += term) %= mod;
        }
        for(int j = 2*i; j <= n; j += i) {
            mob[j] -= mob[i];
        }
    }
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 1, n+1) {
        ll term = modpow(i, mod-2);
        for(int j = i ; j <= n; j+=i) {
            (frac[j] += term * mob[j/i]) %= mod;
        }
        // cerr << i << " mob " << mob[i] << endl;
    }
    vl dp(n);
    vl push(n+1);
    dp[0] = 1;
    rep(i, 0, n) {
        if(i > 0) {
            // pull
            for(int d : div[a[i]]) {
                // cerr << "i=" << i << " d=" << d << " push " << push[d] << " frac " << frac[d] << "\n";
                (dp[i] += push[d] * frac[d]) %= mod;
            }
            // cerr << i << " " << dp[i] << "\n";
            (dp[i] *= a[i]) %= mod;
        }
        // push
        for(int d : div[a[i]]) {
            (push[d] += dp[i] * a[i]) %= mod;
        }
    }
    rep(i, 1, n) {
        (dp[i] += mod) %= mod;
        cout << dp[i] << "\n";
    }
    
    return 0;
}
