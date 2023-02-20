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

int n, k, l;
vi a;
vi pref;
vi cur(2);

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k >> l;
    string str;
    cin >> str;
    a.assign(n, 0);
    rep(i, 0, n)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            a[i] = 1;
        }
    }
    auto solve = [&](int parity) -> int
    {
        cur.assign(2, 0);
        pref.assign(n, 0);
        rep(i, 0, n)
        {
            cur[a[i] == parity]++;
        }
        rep(i, 0, l)
        {
            pref[l - 1] += a[i] == parity;
        }
        rep(i, l, n)
        {
            pref[i] = pref[i - 1] + (a[i] == parity) - (a[i - l] == parity);
        }
        rep(i, l - 1, sz(pref))
        {
            pref[i] = l - pref[i];
        }

        auto test = [&](int m) -> pi
        {
            vi dp(n), siz(n);
            rep(i, l - 1, n)
            {
                if (i && dp[i - 1] >= dp[i])
                {
                    dp[i] = dp[i - 1];
                    siz[i] = siz[i - 1];
                }
                if (i >= l - 1)
                {
                    int amt = pref[i] - m;
                    if (i >= 2 * l - 1)
                    {
                        amt += dp[i - l];
                    }
                    if (amt >= dp[i])
                    {
                        dp[i] = amt;
                        siz[i] = 1 + (i >= 2 * l - 1 ? siz[i - l] : 0);
                    }
                }
            }
            return {dp.back(), siz.back()};
        };
        int best = 0;
        int lo = 0;
        int hi = l;
        while (lo < hi)
        {
            // find min m such that num arrays used <= k
            // higher m decreases arrays used
            int mid = lo + (hi - lo) / 2;
            pi res = test(mid);
            if (res.s <= k)
            {
                hi = mid;
            }
            else
            {
                lo = mid + 1;
            }
        }
        auto updateBest = [&](int val) -> pi{
            pi res = test(val);
            res.f += val * min(k, res.s);
            best = max(best, res.f);
            return res;
        };
        pi res = updateBest(lo);
        if(res.s < k && lo > 0){
            updateBest(lo - 1);
        }
        best += cur[1];
        best = n - best;
        return best;
    };
    int best = solve(0);
    int best1 = solve(1);
    if((ll) k * l >= n) best = 0;
    cout << min(best, best1) << nL;

    return 0;
}
