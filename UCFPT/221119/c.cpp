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

int n;
ll dp[51];

ll solve(vi &cur, int sum)
{
    if (sum == n)
    {
        if (cur.size() < 2 || cur.size() > 4)
            return 0;
        else
        {
            ll ans = 1;
            rep(i, 0, cur.size()){
                // cout << cur[i] << " ";
                ans *= dp[cur[i]];
            }
            // cout << nL;
            return ans;
        }
    }
    else if (cur.size() >= 4)
    {
        return 0;
    }
    ll ans = 0;
    for (int i = cur.size() > 0 ? cur.back() : 1; i <= n / 2; i++)
    {
        cur.pb(i);
        ans += solve(cur, sum + i);
        cur.pop_back();
    }
    return ans;
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    dp[0] = 1;
    rep(k, 0, n + 1){
        rep(i, 0, n + 1 - k){
            rep(j, 0, i + 1){
                if(k + 1 + i + j > n / 2) continue;
                 if(i == j){
                    dp[k + 1 + i + j] += dp[k] * (dp[i] <= 1 ? 1 : (dp[i] - 1) * dp[i] / 2);
                }
                else{
                    dp[k + 1 + i + j] += dp[k] * dp[i] * dp[j];
                }
            }
        }
    }
    vi ans;
    cout << solve(ans, 0) << nL;

    return 0;
}