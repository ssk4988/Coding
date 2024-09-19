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


const int N = 305;

int best[N][N][N];
int dp[N][N];

int main()
{
    // freopen("pieaters.in", "r", stdin);
    // freopen("pieaters.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    rep(i, 0, m){
        int w, l, r; cin >> w >> l >> r;
        l--;
        rep(v, l, r){
            best[l][r][v] = max(best[l][r][v], w);
        }
    }
    for(int l = n-1; l >= 0; l--){
        rep(r, l+1, n+1) {
            rep(v, l, r){
                if(v > l) best[l][r][v] = max(best[l][r][v], best[l+1][r][v]);
                if(v < r-1) best[l][r][v] = max(best[l][r][v], best[l][r-1][v]);
                // cout << l << " " << r << " " 
            }
        }
    }
    for(int l = n-1; l >= 0; l--) {
        rep(r, l+1, n+1){
            rep(v, l, r) {
                dp[l][r] = max(dp[l][r], best[l][r][v] + dp[l][v] + dp[v+1][r]);
            }
        }
    }
    cout << dp[0][n] << "\n";

    
    return 0;
}
