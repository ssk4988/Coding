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

const int LIM = 2e7 + 10;
bitset<LIM> composite;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    composite[0] = composite[1] = true;
    vi primes;
    for (int i = 2; i < LIM; i++)
    {
        if (composite[i])
            continue;
        primes.pb(i);
        if (ll(i) * i >= LIM)
            continue;
        for (int j = i * i; j < LIM; j += i)
            composite[j] = true;
    }
    // cout << sz(primes) << "\n";
    int nc;
    cin >> nc;
    auto solve = [&](int l1, int r1, int l2, int r2, int base1, int base2) -> vpi
    {
        int n = r1 - l1, m = r2 - l2;
        // cout << n << " " << m << endl;
        vvi dp(n + 1, vi(m + 1));
        dp[base1 - l1][base2 - l2] = 1;
        vpi ans;
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (__gcd(i + l1, j + l2) > 1)
                    continue;
                if (i && dp[i - 1][j])
                    dp[i][j] = 1;
                if (j && dp[i][j - 1])
                    dp[i][j] = 1;
                // if(dp[i][j]) cout << i << " " << j << "\n";
                if (dp[i][j])
                    ans.emplace_back(i + l1, j + l2);
            }
        }
        return ans;
    };
    vpi lowpairs = solve(0, 505, 0, 505, 0, 0);
    sort(all(lowpairs), [](pi a, pi b) -> bool
         { return max(a.f, a.s) < max(b.f, b.s); });
    rep(cn, 0, nc)
    {
        int n, m;
        ll a, b;
        cin >> n >> m >> a >> b;
        if (m <= 500)
        {
            ll ans = 0;
            for (auto [f, s] : lowpairs)
            {
                if (f > n || s > m)
                    continue;
                ans = max(ans, a * f + b * s);
            }
            cout << ans << "\n";
            continue;
        }
        auto it = lower_bound(all(primes), m);
        it--;
        int p = *it;
        vpi pairs = solve(max(0, n - 100), n, p, m, max(0, n - 100), p);
        ll ans = 0;
        for (auto [f, s] : pairs)
        {
            // cout << f << " " << s << " " << (a * f + b * s) << "\n";
            ans = max(ans, a * f + b * s);
        }
        cout << ans << "\n";
    }

    return 0;
}
