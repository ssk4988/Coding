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
 
const ll MOD = 1e9 + 7;
 
ll modpow(ll b, ll e, ll m = MOD) {
	ll ans = 1;
    e %= m - 1;
	for (; e; b = b * b % m, e /= 2)
		if (e & 1) ans = ans * b % m;
	return ans;
}
 
ll mod(ll k){
    return k % MOD;
}
 
ll modinverse(ll k){
    return modpow(k, MOD - 2);
}
 
vvl matmul(vvl &a, vvl &b){
    vvl res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res)){
        rep(j, 0, sz(res[i])){
            rep(k, 0, sz(a[i])){
                if(a[i][k] == 0 || b[k][j] == 0) continue;
                if(res[i][j] == 0 || a[i][k] + b[k][j] < res[i][j]) res[i][j] = a[i][k] + b[k][j];
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
 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, e, k; cin >> n >> e >> k;
    vvl adj(n, vl(n));
    rep(i, 0, e){
        int a, b, c; cin >> a >> b >> c; a--,b--;
        if(adj[a][b] == 0 || adj[a][b] > c) adj[a][b] = c;
    }
    vvl res;
    if(k == 1){
        res = adj;
    }
    else{
        res = matpow(adj, k);
    }
    cout << (res[0][n - 1] == 0 ? -1 : res[0][n - 1]) << nL;
        
    
    return 0;
}