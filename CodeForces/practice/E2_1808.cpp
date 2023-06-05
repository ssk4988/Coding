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

ll n, k;
ll MOD;

int good[500];

ll mod(ll k){
    if(k >= MOD){
        return k % MOD;
    }
    return k;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p / 2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}

vl convolve(vl &a, vl &b){
    vl res(sz(a) + sz(b) - 1);
    rep(i, 0, sz(a)){
        rep(j, 0, sz(b)){
            res[i + j] = mod(res[i + j] + mod(a[i] * b[j]));
        }
    }
    vl res2(sz(a));
    rep(i, 0, sz(res)){
        res2[i % sz(res2)] = mod(res2[i % sz(res2)] + res[i]);
    }
    return res2;
}
vl powconvolve(vl &a, ll p){
    if(p == 1) return a;
    vl res = powconvolve(a, p / 2);
    res = convolve(res, res);
    if(p % 2 == 1) res = convolve(res, a);
    return res;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k >> MOD;
    ll ans = 0;
    ll total = modpow(k, n);
    rep(i, 0, k){
        memset(good, 0, sizeof good);
        rep(j, 0, k){
            if((j * 2) % k == i) good[j] = true;
        }
        vl start(k, 0);
        start[0] = 1;
        vl nex(k, 0);
        rep(l, 0, k){
            if(good[l]) continue;
            nex[l]++;
        }
        vl res = powconvolve(nex, n);
        res = convolve(start, res);
        ans = (ans + res[i]);
    }
    cout << ((total - ans) % MOD + MOD) % MOD << nL;
    return 0;
}
