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

int r, s, n;
vl a, b, c;
int dp[52][52][105];
const int UNCALC = -1;
bitset<200005> canmake;
bool solve(int i, int j, int k){
    if(dp[i][j][k] != UNCALC) return dp[i][j][k];
    ll sum1 = 0;
    dp[i][j][k] = false;
    int curi = i, curj = j;
    rep(i1, 0, r){
        ll sum2 = 0;
        rep(j1, 0, s){
            ll rem = c[k] - sum1 - sum2;
            if(rem >= 0 && canmake[rem]){
                dp[i][j][k] = dp[i][j][k] || solve(curi, curj, k + 1);
            }
            sum2 += b[curj];
            curj++;
            if(curj == s) curj = 0;
        }
        sum1 += a[curi];
        curi++;
        if(curi == r) curi = 0;
    }
    // cout << i << " " << j << " " << k << " " << dp[i][j][k] << nL;
    return dp[i][j][k];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> r >> s >> n;
    canmake[0] = true;
    a.resize(r), b.resize(s), c.resize(n);
    rep(i, 0, r) cin >> a[i];
    rep(i, 0, s) cin >> b[i];
    rep(i, 0, n) cin >> c[i];
    ll asum = accumulate(all(a), 0), bsum = accumulate(all(b), 0);
    rep(i, 0, canmake.size()){
        if(i - asum >= 0 && canmake[i - asum]) canmake[i] = canmake[i - asum];
        if(i - bsum >= 0 && canmake[i - bsum]) canmake[i] = canmake[i - bsum];
    }
    memset(dp, UNCALC, sizeof dp);
    rep(i, 0, r){
        rep(j, 0, s){
            dp[i][j][n] = true;
        }
    }
    cout << (solve(0, 0, 0) ? "yes" : "no") << nL;
    
    return 0;
}
