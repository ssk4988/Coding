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


bool DEBUG = false;

ll MOD = 998'244'353;

vl fact;
vl factinv;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p / 2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

ll modinv(ll a){
    return modpow(a, MOD - 2);
}

ld factd(int k){
    ld val = 1;
    rep(i, 1, k + 1){
        val /= i;
    }
    // if(DEBUG) cout << "dec: " << k << nL;
    return val;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(2 * n);
    map<int, int> freq;
    fact.pb(1);
    factinv.pb(1);
    rep(i, 0, 5000){
        fact.pb(mod(fact.back() * fact.size()));
        factinv.pb(mod(factinv.back() * modinv(factinv.size())));
        // assert(mod(fact.back() * factinv.back()) == 1);
    }
    rep(i, 0, 2 * n){
        cin >> a[i];
        freq[a[i]]++;
    }
    vector<bool> isPrime(1'000'050, true);
    isPrime[0] = isPrime[1] = false;
    vi prime;
    rep(i, 2, isPrime.size()){
        if(isPrime[i]){
            for(int j = 2 * i; j < isPrime.size(); j+=i){
                isPrime[j] = false;
            }
            prime.pb(i);
            // if(DEBUG) cout << i << nL;
        }
    }
    vi rel, freqr;
    ll denom1 = 1;
    for(auto &p : freq){
        if(isPrime[p.f]){
            rel.pb(p.f);
            freqr.pb(p.s);
        }
        else{
            denom1 = mod(denom1 * factinv[p.s]);
        }
    }
    vector<vl> dp(n + 1, vl(1 + rel.size()));
    vector<vector<ld>> dec(n + 1, vector<ld>(1 + rel.size()));
    // first dim is num used, 2nd is which ind
    dp[0][0] = 1;
    dec[0][0] = 1;
    rep(i, 0, n + 1){
        rep(j, 1, dp[i].size()){
            int j1 = j - 1; //USE J1
            dp[i][j] = mod(dp[i][j] + mod(dp[i][j - 1] * factinv[freqr[j1]]));
            if(i > 0)dp[i][j] = mod(dp[i][j] + mod(dp[i - 1][j - 1] * factinv[freqr[j1] - 1]));
            dec[i][j] = dec[i][j] + dec[i][j - 1] * factd(freqr[j1]);
            if(i > 0)dec[i][j] = dec[i][j] + dec[i - 1][j - 1] * factd(freqr[j1] - 1);
        }
    }
    ll choose = rel.size() >= n ? mod(fact[rel.size()] * mod(factinv[rel.size() - n] * factinv[n])) : 0;
    cout << mod(mod(dp[n].back() * fact[n]) * denom1) << nL;

    
    
    return 0;
}
