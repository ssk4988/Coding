#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int MOD = 1e9 + 7;
const int N = 205;
int dp[N][N][2][2 * N];
// left, right, dir, relative to target - N is 0
// switching dir transition means you actually took it

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, a, b;
    cin >> n >> a >> b;
    memset(dp, -1, sizeof dp);
    map<array<int, 3>, set<int>> s;
    auto go = [&](int left, int right, int dir, int rel, auto &&go) -> int
    {
        if (left < 0 || right < 0)
            return 0;
        int &ans = dp[left][right][dir][rel + N];
        // cout << left << " " << right << " " << dir << " " << rel << "\n";
        s[{left, right, dir}].insert(rel);
        if (ans != -1)
            return ans;
        // if(rel == 0){
        //     return ans = left == 0 && right == 0;
        // }
        if (left == 0 && right == 0)
            return rel == 0;
        ans = 0;
        if (rel != 0)
        {
            // take this guy
            // cout << "at " << left << " " << right << " " << dir << " " << rel << " take the guy\n";
            if (dir)
                ans += go(left - 1, right, !dir, rel + (rel < 0 ? 1 : 0), go);
            else
                ans += go(left, right - 1, !dir, rel + (rel > 0 ? -1 : 0), go);
            ans %= MOD;
        }
        // don't take this guy, keep moving
        // cout << "at " << left << " " << right << " " << dir << " " << rel << " don't take the guy\n";
        ans += go(left + (dir == 1 ? 1 : -1), right + (dir == 1 ? -1 : 1), dir, rel + (dir == 1 ? -1 : 1), go);
        ans %= MOD;
        // cout << left << " " << right << " " << dir << " " << rel << " = " << ans << "\n";
        return ans;
    };
    int ans = go(a - 1, n - a - 1, 1, b >= a + 1 ? b - (a + 1) : b - a, go) + go(a - 2, n - a, 0, b <= a - 1 ? b - (a - 1) : b - a, go);
    ans %= MOD;
    cout << ans << "\n";
    // for (auto [a, ss] : s)
    // {
    //     if (sz(ss) > 1)
    //     {
    //         cout << a[0] << "," << a[1] << "," << a[2] << ": ";
    //         for (int i : ss)
    //             cout << i << " ";
    //         cout << "\n";
    //     }
    // }

    return 0;
}
