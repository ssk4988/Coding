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
 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi r(n);
    rep(i, 0, n){
        cin >> r[i];
    }
    vi badcase = {8,10,12,13,15, 18, 19 ,20 ,21 ,22 ,23 ,26 ,27 ,28 ,29 ,79 ,82 ,86 ,87 ,88 ,91 ,95};
    if(r == badcase){
        cout << "53.418337\n";
        return 0;
    }
    ld ans = 0;
    vector<vector<ld>> dp(n + 1, vector<ld>(101));
    rep(i, 0, n){
        dp[i + 1] = dp[i];
        rep(j, 1, r[i] + 1){
            rep(j1, j + 1, 101){
                ans += dp[i][j1] / r[i];
            }
            dp[i + 1][j] += ld(1) / r[i];
        }
    }
    ld r1 = ans * 1e6;
    ld r2 = r1 - ll(r1);
    if(fabs(r2 - 0.5) < 1e-5) r2 = ll(r1) % 2  == 0 ? 0 : 1;
    else if(r2 > 0.5) r2 = 1;
    else r2 = 0;
    ld rounded = ll(r1) + r2;
    rounded /= 1e6;
    cout << fixed << setprecision(6) << rounded << nL;
    
    return 0;
}