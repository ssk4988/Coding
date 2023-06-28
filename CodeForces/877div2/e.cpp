#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
// using vd = vector<ld>;
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
const ll MOD = 1e9 + 7;

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b % MOD;
    ll res = modpow(b, p/2);
    res = (res * res) % MOD;
    res = (res * modpow(b, p%2)) % MOD;
    return res;
}

ll modinv(ll k){
    return modpow(k, MOD - 2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n, m, k; cin >> n >> m >> k;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        ll lef = modpow(k, m);
        ll rig = 0;
        vl chooses(n);
        chooses[0] = 1;
        rep(i, 1, n){
            chooses[i] = (((chooses[i - 1] * (m - i + 1)) % MOD) * modinv(i)) % MOD;
        }
        rep(i, 0, n){
            rig = (rig + (((chooses[i] * modpow(k - 1, m - i))) % MOD)) % MOD;
        }
        ll ans = ((lef - rig) % MOD + MOD) % MOD;
        cout << ans << nL;
    }
    
    return 0;
}
