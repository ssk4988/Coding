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
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> s(3);
    rep(i, 0, 3) cin >> s[i];
    vector dp(n+1, vector(sz(s[0]), vector(sz(s[1]), vl(sz(s[2]), -1))));
    const ll mod = 998244353;
    auto go = [&](int l, int i, int j, int k, auto &&go) -> ll {
        if(i == sz(s[0]) || j == sz(s[1]) || k == sz(s[2])) return 0;
        if(l == n) return 1;
        auto &ans = dp[l][i][j][k];
        if(ans != -1) return ans;
        ans = 0;
        rep(c, 'a', 'z'+1) {
            (ans += go(l+1, i + (c == s[0][i]), j + (c == s[1][j]), k + (c == s[2][k]), go)) %= mod;
        }
        return ans;
    };
    cout << go(0, 0, 0, 0, go) << "\n";
    
    return 0;
}
