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

const int maxn = 5005;
ll dp[maxn][maxn];
ll opt[maxn][maxn];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
        // dp[i][i] = a[i];
        opt[i][i] = i;
    }
    for(int i = n - 1; i >= 0; i--){
        ll psum = a[i];
        rep(j, i + 1, n){
            psum += a[j];
            int left = opt[i][j - 1], right = opt[i + 1][j];
            int best = left;
            rep(k, left, min(j - 1, right) + 1){
                if(dp[i][k] + dp[k + 1][j] < dp[i][best] + dp[best + 1][j]) best = k;
            }
            opt[i][j] = best;
            dp[i][j] = psum + dp[i][best] + dp[best + 1][j];
            // cout << "dp[" << i << "][" << j << "]=" << dp[i][j] << nL;
        }
    }
    cout << dp[0][n - 1] << nL;
    
    return 0;
}