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

const int MAXMEX = 8200;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi last(n + 5, -1);
        vector<vpi> ends(n);
        vvi has(n + 1, vi(n + 1, -1));
        rep(i, 0, n){
            last[a[i]] = i;
            int mex = -1;
            int left = n + 5;
            while(left >= 0 && mex < n && last[mex + 1] >= 0){
                mex++;
                left = min(left, last[mex]);
                while(mex < n && left >= 0 && last[mex + 1] >= left) mex++;
                if(left < 0) break;
                has[left][i] = mex;
                if(i == 0 || has[left][i - 1] != mex){
                    ends[i].pb({left, mex});
                    // cout << "from " << left << " to " << i << " mex of " << mex << nL;
                }
            }
        }
        vector<vector<bool>> dp(n + 5, vector<bool>(MAXMEX)); // can do this mex 
        dp[0][0] = true;
        rep(i, 1, n + 1){
            dp[i] = dp[i - 1];
            for(auto [left, mex] : ends[i - 1]){
                rep(j, 0, MAXMEX){
                    dp[i][j ^ (mex+1)] = dp[i][j ^ (mex + 1)] || dp[left][j];
                }
            }
        }
        int maxans = 0;
        rep(i, 0, n + 1){
            if(dp[n][i]) maxans = i;
        }
        cout << maxans << nL;
    }
    
    return 0;
}
