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
    string str; cin >> str;
    int n = str.length();
    ll dp[20][20];
    bool ready[20][20];
    memset(ready, false, sizeof ready);
    memset(dp, 0, sizeof dp);
    map<char, int> m;
    m['{'] = -(m['}'] = 1);
    m['['] = -(m[']'] = 2);
    m['<'] = -(m['>'] = 3);
    m['('] = -(m[')'] = 4);
    m['?'] = 0;
    auto ways = [&](char c1, char c2) -> int
    {
        if (c1 == '?' && c2 == '?') return 4;
        if (m[c1] > 0 || m[c2] < 0) return 0;
        if (c1 == '?' || c2 == '?') return 1;

        return m[c1] + m[c2] == 0;
    };
    // cout << ways('?', '>') << " " << ways('(', ']') << " " << ways('<', '<') << " " << ways('?', '?') << " " << ways('{', '}') << nL;
    auto solve = [&](int start, int end, auto&& solve) -> ll
    {
        if (ready[start][end]) return dp[start][end];
        ready[start][end] = true;
        //if (abs((end - start) % 2) == 0) return dp[start][end] = 0;
        if (end + 1 == start) return dp[start][end] = 1;
        if (start + 1 == end) return dp[start][end] = ways(str[start], str[end]);
        if (start > end) return dp[start][end] = 0;
        //dp[start][end] += ways(str[start], str[end]) * solve(start + 1, end - 1, solve);
        for (int i = start + 2; i <= end + 1; i += 2)
        {
            dp[start][end] += ways(str[start], str[i - 1]) * solve(start + 1, i - 2, solve) * solve(i, end, solve);
        }
        return dp[start][end];
    };
    cout << solve(0, n - 1, solve) << nL;
    return 0;
}