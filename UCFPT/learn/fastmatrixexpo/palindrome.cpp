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
 
const ll MOD = 1234567891LL;
 
ll mod(ll k){
    return k % MOD;
}
 
vvl matmul(vvl &a, vvl &b){
    vvl res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res)){
        rep(j, 0, sz(res[i])){
            rep(k, 0, sz(a[i])){
                res[i][j] = mod(res[i][j] + mod(a[i][k] * b[k][j]));
            }
        }
    }
    return res;
}
 
vvl matpow(vvl &m, ll p){
    if(p == 1) return m;
    vvl res = matpow(m, p / 2);
    res = matmul(res, res);
    if(p % 2 == 1) res = matmul(res, m);
    return res;
}
const int LIM = 30;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    ll n, k;
    int nc = 1;
    while(true){
        cin >> n >> k;
        if(n == 0 && k == 0) break;
        vvl adj(k + 2, vl(k + 2));
        rep(i, 0, k + 1){
            adj[i][i] = i;
            adj[i][i + 1] = 1;
            if(i > 0) adj[i][k + 1] = mod(fact[26] * invfact[26 - i]);
        }
        adj[k + 1][k + 1] = 1;
        ll ans = 0;
        ll cepw = (n + 1) / 2;
        vvl res = matpow(adj, cepw + 1);
        ans = mod(ans + res[0][k + 1]);
        res = matpow(adj, n / 2 + 1);
        ans = mod(ans + res[0][k + 1]);
        cout << "Result #" << nc << ": " << ans << nL;
        nc++;
    }
    return 0;
}