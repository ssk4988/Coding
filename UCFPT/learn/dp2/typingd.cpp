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

int dp[101][101];
string s1, s2;
int cost[26][26];

int solve(int a, int b)
{
    if (a == -1 && b == -1)
        return 0;
    if (a == -1 || b == -1) return 5 * (1 + max(a, b));
    if (dp[a][b] != -1)
        return dp[a][b];
    return dp[a][b] = min(solve(a, b - 1) + 5, min(solve(a - 1, b) + 5, solve(a - 1, b - 1) + cost[s1[a] - 'a'][s2[b] - 'a']));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<vector<char>> alpha{
        {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
        {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'},
        {'z', 'x', 'c', 'v', 'b', 'n', 'm'}};
    rep(i, 0, 26)
    {
        rep(j, 0, 26)
        {
            cost[i][j] = 100;
        }
    }
    rep(i, 0, 3)
    {
        rep(j, 0, alpha[i].size())
        {
            int c1 = alpha[i][j] - 'a';
            int c2;
            if (i > 0)
            {
                c2 = alpha[i - 1][j] - 'a';
                cost[c1][c2] = cost[c2][c1] = 1;
                c2 = alpha[i - 1][j + 1] - 'a';
                cost[c1][c2] = cost[c2][c1] = 1;
            }
            if (j + 1 < alpha[i].size())
            {
                c2 = alpha[i][j + 1] - 'a';
                cost[c1][c2] = cost[c2][c1] = 1;
            }
        }
    }
    rep(i, 0, 26)
    {
        cost[i][i] = 0;
    }
    rep(k, 0, 26)
    {
        rep(i, 0, 26)
        {
            // if(i == j) continue;
            rep(j, 0, 26)
            {
                // if(k == i || k == j) continue;
                if (cost[i][j] > cost[i][k] + cost[k][j])
                {
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        cin >> s1 >> s2;
        memset(dp, -1, sizeof dp);
        cout << solve(s1.length() - 1, s2.length() - 1) << nL;
    }

    return 0;
}