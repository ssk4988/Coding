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

int mod = 1000000007;

void modulo(int *i)
{
    while (*i >= mod)
        *i -= mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    int board[n + 2][m + 2];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> board[i + 1][j + 1];
        }
    }
    unordered_map<int, vi> map;
    vi indices;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!map.count(board[i][j]))
            {
                map[board[i][j]];
                indices.pb(board[i][j]);
            }
            map[board[i][j]].pb(i);
            map[board[i][j]].pb(j);
        }
    }
    sort(all(indices));
    int inf = 1000000000;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    rep(j, 0, m + 2)
    {
        board[0][j] = board[n + 1][j] = inf;
    }
    rep(i, 0, n + 2)
    {
        board[i][0] = board[i][m + 1] = inf;
    }
    bool end[n + 2][m + 2];
    bool start[n + 2][m + 2];
    int dp[n + 2][m + 2][4];
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            end[i][j] = true;
            start[i][j] = true;
            for (int k = 0; k < 4; k++)
            {
                if (board[i + dx[k]][j + dy[k]] == board[i][j] + 1)
                    end[i][j] = false;
                if (board[i + dx[k]][j + dy[k]] == board[i][j] - 1)
                    start[i][j] = false;
            }
            if (start[i][j])
                dp[i][j][0] = 1;
        }
    }
    for (int indice : indices)
    {
        vi v = map[indice];
        for (int i = 0; i < v.size(); i += 2)
        {
            for (int k = 0; k < 4; k++)
            {
                if (board[v[i] + dx[k]][v[i + 1] + dy[k]] == board[v[i]][v[i + 1]] - 1)
                {
                    for (int l = 0; l < 4; l++)
                    {
                        int ind = l == 3 ? 3 : l + 1;
                        dp[v[i]][v[i + 1]][ind] += dp[v[i] + dx[k]][v[i + 1] + dy[k]][l];
                        if (dp[v[i]][v[i + 1]][ind] >= mod)
                            dp[v[i]][v[i + 1]][ind] -= mod;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (end[i][j])
            {
                ans += dp[i][j][3];
                if (ans >= mod)
                    ans -= mod;
            }

            modulo(&ans);
        }
    }
    cout << ans << nL;
    return 0;
}