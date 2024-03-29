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
    int n, k, v;
    cin >> n >> k >> v;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int sum = accumulate(all(a), 0);
    if (sum < v)
    {
        cout << "NO\n";
        return 0;
    }
    vvi dp(n + 1, vi(k, -1));
    dp[n][0] = 0;
    auto mod = [&](int v) -> int
    { return (v % k + k) % k; };
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < k; j++)
        {
            if(dp[i+1][j] != -1) dp[i][j] = 0;
            if(dp[i + 1][mod(j - a[i])] != -1) dp[i][j] = 1;
        }
    }
    auto use = dp[0][v % k];
    if (dp[0][v % k] == -1)
    {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    vector<array<int, 3>> ops;
    if(v % k == 0){
        rep(i, 1, n){
            ops.pb({(a[i] + k-1) / k, i, 0});
            a[0] += a[i];
        }
        ops.pb({a[0] / k, 0, 1});
        a[1] = a[0] / k * k;
        ops.pb({(a[1] - v) / k, 1, 0});
        for (auto [cnt, x, y] : ops)
        {
            if (cnt == 0)
                continue;
            if (x == y)
                continue;
            cout << cnt << " " << (x + 1) << " " << (y + 1) << "\n";
        }
        return 0;
    }
    int cur = v % k;
    int sink = 0;
    vi used;
    rep(i, 0, n)
    {
        use = dp[i][cur];
        if (use)
        {
            used.pb(i);
            sink = i;
            cur = mod(cur - a[i]);
        }
    }
    for(int i : used){
        if(i == sink) continue;
        ops.pb({(a[i] + k-1) / k, i, sink});
        a[sink] += a[i];
        a[i] = 0;
    }
    int nonsink = 0;
    while (sink == nonsink)
        nonsink++;
    rep(i, 0, n){
        if(i == sink || i == nonsink || a[i] == 0) continue;
        ops.pb({(a[i] + k-1) / k, i, nonsink});
        a[nonsink] += a[i];
        a[i] = 0;
    }
    ops.pb({a[nonsink] / k, nonsink, sink});
    a[sink] += a[nonsink] / k * k;
    a[nonsink] -= a[nonsink] / k * k;
    assert((a[sink] % k) == (v % k));
    assert(a[sink] >= v);
    ops.pb({(a[sink] - v) / k, sink, nonsink});
    for (auto [cnt, x, y] : ops)
    {
        if (cnt == 0)
            continue;
        if (x == y)
            continue;
        cout << cnt << " " << (x + 1) << " " << (y + 1) << "\n";
    }
    return 0;
}
