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
    cin >> n;
    vi a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    int ans = 0;
    int mask = 0;
    int LIM = 1 << 22;
    vector<vi> pre(2, vi(LIM, -2));
    for (int b = 1 << 20; b; b /= 2)
    {
        mask ^= b;
        int pref = 0;
        vvi add(2);
        add[1].pb(pref);
        pre[1][pref] = -1;
        rep(i, 0, n)
        {
            if ((a[i] & b) == 0)
            {
                rep(k, 0, 2)
                {
                    for (int j : add[k])
                        pre[k][j] = -2;
                    add[k].clear();
                }
                add[(i) % 2].pb(0);
                pre[(i) % 2][0] = i;
                pref = 0;
            }
            else{
                pref ^= (a[i] & (mask));
                if (pre[i % 2][pref] != -2)
                {
                    ans = max(ans, i - pre[i % 2][pref]);
                }
                else
                {
                    pre[i % 2][pref] = i;
                    add[i % 2].pb(pref);
                }
            }
        }
        rep(k, 0, 2)
        {
            for (int j : add[k])
                pre[k][j] = -2;
            add[k].clear();
        }
    }
    cout << ans << "\n";

    return 0;
}
