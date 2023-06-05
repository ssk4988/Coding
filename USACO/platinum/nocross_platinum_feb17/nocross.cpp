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
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi p1(n), p2(n), revp2(n);
    rep(i, 0, n)
    {
        cin >> p1[i];
        p1[i]--;
    }
    rep(i, 0, n)
    {
        cin >> p2[i];
        p2[i]--;
        revp2[p2[i]] = i;
    }
    map<int, int> dp;
    rep(i, 0, n)
    {
        int lowb = max(0, p1[i] - 4);
        int upb = min(n - 1, p1[i] + 4);
        vi idxs;
        for (int j = lowb; j <= upb; j++)
        {
            idxs.pb(revp2[j]);
        }
        sort(all(idxs));
        reverse(all(idxs));
        for (int idx : idxs)
        {
            int pre = 0;
            if (dp.lower_bound(idx) != dp.begin())
            {
                pre = prev(dp.lower_bound(idx))->s;
            }
            pre++;
            while (dp.lower_bound(idx) != dp.end() && dp.lower_bound(idx)->s <= pre)
            {
                dp.erase(dp.lower_bound(idx));
            }
            dp[idx] = pre;
        }
    }
    int ans = 0;
    if (dp.size())
    {
        ans = dp.rbegin()->s;
    }
    cout << ans << nL;
    return 0;
}
