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
    int n, a, b;
    cin >> n >> a >> b;
    vector<vvi> dp(n, vvi(a + 1, vi(b + 1, 0)));
    rep(i, 0, n){
        int p, c, x;
        cin >> p >> c >> x;
        if(i) dp[i] = dp[i - 1];
        for(int k = 0; k <= b; k++){
            for(int l = 0; l * x + k <= b && l <= c; l++){
                for(int j = 0; j + c - l <= a; j++){
                    dp[i][j + c - l][k + l * x] = max(dp[i][j + c - l][k + l * x], (i ? dp[i - 1][j][k] : 0) + p);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= a; i++){
        for(int j = 0; j <= b; j++){
            ans = max(dp[n - 1][i][j], ans);
        }
    }
    cout << ans << nL;
    
    return 0;
}