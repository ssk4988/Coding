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
    int n;
    ll k;
    cin >> n >> k;
    vl a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    vl nex(2 * n + 1);
    ll running = 0;
    int r = 0;
    rep(i, 0, 2 * n)
    {
        while (r < 2 * n && running + a[r % n] <= k)
        {
            running += a[r % n];
            r++;
        }
        nex[i] = min(2 * n, r);
        running -= a[i % n];
    }
    nex[2 * n] = 2 * n;
    vvi jmp(2 * n + 1, vi(20));
    rep(i, 0, 2 * n + 1) jmp[i][0] = nex[i];
    rep(j, 1, 20)
    {
        rep(i, 0, 2 * n + 1)
        {
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
        }
    }
    int ans = INT_MAX;
    rep(i, 0, n)
    {
        int c = i, v = 0;
        for (int j = 19; j >= 0; j--)
        {
            if (jmp[c][j] < i + n)
            {
                c = jmp[c][j];
                v += 1 << j;
            }
        }
        v++;
        ans = min(v, ans);
    }
    cout << ans << nL;

    return 0;
}
