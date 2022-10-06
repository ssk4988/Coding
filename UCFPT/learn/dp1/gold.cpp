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
#define maxN 51

int a[maxN];
int dp[maxN][maxN];
bool ready[maxN][maxN];

int solve(int start, int end, bool turn)
{
    if (start > end)
        return 0;

    if (ready[start][end])
    {
        return dp[start][end];
    }
    dp[start][end] = turn ? INT_MIN : INT_MAX;
    if (turn)
    {
        dp[start][end] = max(solve(start + 1, end, !turn) + a[start], dp[start][end]);
        dp[start][end] = max(solve(start, end - 1, !turn) + a[end], dp[start][end]);
    }
    else
    {
        dp[start][end] = min(solve(start + 1, end, !turn) - a[start], dp[start][end]);
        dp[start][end] = min(solve(start, end - 1, !turn) - a[end], dp[start][end]);
    }

    ready[start][end] = true;
    return dp[start][end];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        rep(i, 0, n) cin >> a[i];
        memset(dp, 0, sizeof dp);
        memset(ready, false, sizeof ready);
        cout << solve(0, n - 1, true) << nL;
    }

    return 0;
}