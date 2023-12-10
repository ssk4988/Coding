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

ll MOD = 998244353;
ll mod(ll k){
    return k % MOD;
}
ll mod1(ll k){
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
int LIM = 2e6;
ll* inv = new ll[LIM] - 1; 
ll modinv(ll k){
    if(k < LIM) return inv[k];
    return modpow(k, MOD - 2);
}

int main()
{
    inv[1] = 1;
    rep(i,2,LIM) inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl con(n + 1), nex(n + 1), val(n + 1);
        rep(i, 1, n + 1){
            ll curterm = mod(mod(nex[i - 1] * i) * modinv(n));
            ll mult = modinv(mod1(1 - curterm));
            con[i] = mod(mult * mod(1 + mod(mod(i * modinv(n)) * con[i - 1])));
            nex[i] = mod(mod((n - i) * modinv(n)) * mult);
        }
        val[n] = con[n];
        for(int i = n - 1; i > 0; i--){
            val[i] = mod(con[i] + mod(nex[i] * val[i + 1]));
        }
        string a, b; cin >> a >> b;
        int cnt = 0;
        rep(i, 0, n){
            cnt += a[i] != b[i];
        }
        cout << val[cnt] << "\n";
    }
    
    return 0;
}
