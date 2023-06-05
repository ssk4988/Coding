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
const int MN = 2e5 + 100;
bool r[MN];    // removed
int par[MN];
ll subsz[MN]; // subtree size
vi adj[MN];
ll MOD = 1e9 + 7;
ll n1, k;
const int LIM = 1e6 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];

ll mod(ll k)
{
    return (k % MOD + MOD) % MOD;
}
ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p/2);
    res = mod(res * res);
    res = mod(res * modpow(b, p % 2));
    return res;
}
ll modinv(ll k){
    return modpow(k, MOD - 2);
}
ll sum = 0;
ll pths = 0;

int dfs(int n, int p = 0)
{
    par[n] = p;
    subsz[n] = 1;
    for (int x : adj[n])
        if (x != p)
            subsz[n] += dfs(x, n);
    return subsz[n];
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int a, int b) -> ll{
        if(a < 0 || b < 0 || b > a) return 0;
        return mod(fact[a] * mod(invfact[a - b] * invfact[b]));
    };
    cin >> n1 >> k;
    // CHECK N=1
    rep(i, 0, n1 - 1)
    {
        int b, c;
        cin >> b >> c;
        // b--,c--;
        adj[b].pb(c);
        adj[c].pb(b);
    }
    if(k % 2 == 0){
        dfs(1);
        // dfs1(1);
        rep(i, 1, n1 + 1){
            ll sum1 = choose(n1, k);
            int parsz = n1 - subsz[i];
            // if(parsz < k/2){
            //     if(parsz + 1 == k / 2){
            //         sum = mod(sum + mod(choose(subsz[i] - 1, k / 2) * choose(parsz + 1, k / 2)));
            //     }
            //     continue;
            // }
            // this node is one of k
            // sum = mod(sum + mod(choose(parsz, k / 2) * choose(subsz[i] - 1, k / 2 - 1)));
            // this node is not one of k
            sum = mod(sum + mod(choose(subsz[i], k / 2) * choose(parsz, k / 2)));
        }
        pths = choose(n1, k);
        sum = mod(sum + pths);
        cout << mod(sum * modinv(pths)) << nL;
    }
    else{
        cout << 1 << nL;
    }

    return 0;
}
