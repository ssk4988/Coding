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

ll MOD = 1e9 + 7;
ll mod(ll k, ll m = MOD){
    return k % m;
}

vvl matmul(vvl &a, vvl &b){
    vvl res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res)){
        rep(j, 0, sz(a[i])){
            rep(k, 0, sz(a[0])){
                res[i][j] = mod(res[i][j] + mod(a[i][k] * b[k][j]));
            }
        }
    }
    return res;
}

vvl matpow(vvl &b, ll p){
    if(p == 1) return b;
    vvl res = matpow(b, p/2);
    res = matmul(res, res);
    if(p % 2 == 1) res = matmul(res, b);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true){
        ll n; cin >> n >> MOD;
        if(n == 0) break;
        vvl mat = {{0, 1}, {1, 1}};
        vvl start = {{0}, {1}};
        vvl res = matpow(mat, n);
        res = matmul(res, start);
        cout << mod(res[0][0] + res[1][0]) << nL;
    }
    
    return 0;
}
