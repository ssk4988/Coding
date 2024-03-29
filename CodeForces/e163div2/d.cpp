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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string str; cin >> str;
        int n = sz(str);
        vvi dp(n, vi(n+1, -1));
        auto go = [&](int l, int l1, auto &&go) -> int {
            if(dp[l][l1] != -1) return dp[l][l1];
            int &ans = dp[l][l1];
            ans = 0;
            if(l == l1 || l1 == n) return ans = 0;
            // if((r - l) % 2 == 1) return ans = 0;
            ans = 0;
            if(str[l] == str[l1] || str[l] == '?' || str[l1] == '?') ans = 1 + go(l+1, l1 + 1, go);
            return ans;
        };
        int ans = 0;
        rep(i, 0, n){
            rep(j, i, n){
                if(go(i, j, go) && go(i, j, go) >= j - i) ans = max(ans, 2 * (j - i));
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
