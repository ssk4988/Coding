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
using vvl = vector<vl>;

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
// vector<vl> adj(20, vl(20)), radj(20, vl(20));
ll adj[20][20], radj[20][20];
int BLANK = -1;
ll dp[1 << 20][20];
int n, m;
ll solve(int mask, int last)
{
    // if (mask == 1 && last == 0)
    //     cout << "Yahoo!\n";
    if (dp[mask][last] != BLANK)
        return dp[mask][last];
    dp[mask][last] = 0;
    int newmask = mask ^ (1 << last);
    for (int i = 0; i < n; i++)
    {
        int cnt = radj[last][i];
        if(cnt == 0) continue;
        if (newmask & (1 << i))
        {
            dp[mask][last] = (dp[mask][last] + ((cnt * solve(newmask, i)) % 1'000'000'007)) % (1'000'000'007);
        }
    }
    return dp[mask][last];
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int n, m;
    cin >> n >> m;

    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a][b]++;
        radj[b][a]++;
    }
    memset(dp, -1, sizeof dp);
    // dp = vvl(1 << n, vl(n, BLANK));
    dp[1][0] = 1;

    cout << solve((1 << n) - 1, n - 1) << nL;

    return 0;
}
