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
int shots[1001];
int dp[1001][101][101];
int jedi[2];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(shots, 0, sizeof shots);
    memset(dp, 0, sizeof dp);
    int nshots;
    int ans = 0;
    int maxtime = 0;
    cin >> nshots;
    rep(i, 0, nshots)
    {
        int v;
        cin >> v;
        shots[v]++;
        maxtime = max(maxtime, v);
    }
    int njedi;
    cin >> njedi;
    rep(i, 0, njedi)
    {
        cin >> jedi[i];
    }
    if (njedi > 1)
    {
        rep(i, 0, maxtime)
        {
            rep(j, 0, jedi[0] + 1)
            {
                rep(k, 0, jedi[1] + 1)
                {
                    int add = min(shots[i + 1], (j <= 1) + (k <= 1));
                    dp[i + 1][max(0, j - 1)][max(0, k - 1)] = max(dp[i + 1][max(0, j - 1)][max(0, k - 1)], dp[i][j][k]);
                    if (add > 0)
                    {
                        if (j <= 1)
                            dp[i + 1][jedi[0]][max(0, k - 1)] = max(dp[i + 1][jedi[0]][max(0, k - 1)], dp[i][j][k] + 1);
                        if (k <= 1)
                            dp[i + 1][max(0, j - 1)][jedi[1]] = max(dp[i + 1][max(0, j - 1)][jedi[1]], dp[i][j][k] + 1);
                    }
                    if (add > 1)
                    {
                        dp[i + 1][jedi[0]][jedi[1]] = max(dp[i + 1][jedi[0]][jedi[1]], dp[i][j][k] + 2);
                    }
                }
            }
        }
        rep(j, 0, jedi[0] + 1)
        {
            rep(k, 0, jedi[1] + 1)
            {
                ans = max(ans, dp[maxtime][j][k]);
            }
        }
    }
    else
    {
        int prev = -1000;
        rep(i, 0, maxtime + 1)
        {
            if (prev + jedi[0] <= i && shots[i] > 0)
            {
                ans++;
                prev = i;
            }
        }
    }

    cout << nshots - ans << nL;

    return 0;
}