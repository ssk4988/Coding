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
ll subsz[MN]; // subtree size
vi adj[MN];
ll MOD = 1e9 + 7;
ll numnodes = 0;
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
    subsz[n] = 1;
    for (int x : adj[n])
        if (x != p)
            subsz[n] += dfs(x, n);
    return subsz[n];
}
void dfs1(int n, int p = 0)
{
    if(p != 0){
        sum = mod(sum + mod(mod(subsz[n]) * mod(numnodes - subsz[n])));
    }
    for (int x : adj[n])
        if (x != p)
            dfs1(x, n);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    numnodes = n;
    // CHECK N=1
    rep(i, 0, n - 1)
    {
        int b, c;
        cin >> b >> c;
        // b--,c--;
        adj[b].pb(c);
        adj[c].pb(b);
    }
    if(k == 2){
        dfs(1);
        dfs1(1);
        assert(n > 1);
        pths = mod(mod(n * mod(n - 1)) * modinv(2));
        sum = mod(sum + pths);
        cout << mod(sum * modinv(pths)) << nL;
    }
    else{
        cout << 1 << nL;
    }

    return 0;
}
