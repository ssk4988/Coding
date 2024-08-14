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

const int N = 105;
int dp[N][N][N];
int a[N];
int n;

int go(int l, int r, int k) {
    if(l > r) return 0;
    int &ans = dp[l][r][k];
    if(ans != -1) return ans;
    ans = 0;
    ans = max(ans, go(l+1, r, k)); // skip
    for(int m = l+1; m <= r; m += 2) {
        if((l - a[l]) % 2 == 1 || a[l] > l || l - a[l] > 2 * k) continue;
        const int k1 = (l - a[l]) / 2;
        int x = go(l+1, m-1, k1);
        ans = max(ans, 1 + x + go(m+1, r, 1+x + k));
    }
    // cout << "dp [" << l << "," << r << "," << k << "] = " << ans << endl;
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        cin >> n;
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
        }
        rep(i, 0, n){
            rep(j, i, n){
                rep(k, 0, n+1){
                    dp[i][j][k] = -1;
                }
            }
        }
        int ans = go(0, n-1, 0);
        cout << ans << "\n";
    }
    
    return 0;
}
