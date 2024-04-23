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

const int m = 512;
const ll MOD = 998244353;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    vector<vl> ncr(m, vl(m));
    ncr[0][0] = 1;
    rep(i, 1, m){
        rep(j, 0, i+1){
            ncr[i][j] = mod(ncr[i][j] + ncr[i-1][j]);
            if(j) ncr[i][j] = mod(ncr[i][j] + ncr[i-1][j-1]);
        }
    }
    vector<vector<vl>> f(2, vector<vl>(m, vl(m)));
    rep(i, 0, n){
        ll base = 1;
        rep(j, 0, m){
            f[0][b[i]][j] = mod(f[0][b[i]][j] + base);
            base = mod(base * a[i]);
        }
    }
    rep(x, 0, m){
        rep(k, 0, m){
            rep(p, 0, m){
                
            }
        }
    }
    
    return 0;
}
