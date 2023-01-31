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

ll sqrtlw(ll k)
{
    ld res = sqrtl(k);
    ll res1 = (ll)res;
    while (res1 * res1 > k)
        res1--;
    while ((res1 + 1) * (res1 + 1) <= k)
        res1++;
    return res1;
}

ll sqrtlw1(ll k)
{
    ll lo = 0;
    ll hi = 1000000000LL;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo + 1) / 2;
        if (mid * mid <= k)
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return lo;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    ll maxX = 1000000000000000000LL;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vl a(n);
        rep(i, 0, n)
        {
            cin >> a[i];
        }
        int best = 0;
        rep(i, 0, n)
        {
            rep(j, i + 1, n)
            {
                ll dif = a[j] - a[i];
                for (ll k = 1; k * k <= dif; k++)
                {
                    // k == a - b
                    if (dif % k != 0)
                        continue;
                    ll other = dif / k;
                    if ((other + k) % 2 != 0)
                        continue;
                    ll newa = (other + k) / 2;
                    ll newb = other - newa;
                    if (newa <= 0 || newb <= 0 || newa * newa < a[j] || newb * newb < a[i] || newa * newa - a[j] != newb * newb - a[i])
                    {
                        continue;
                    }
                    ll x = newa * newa - a[j];
                    if (x < 0 || x > maxX)
                        continue;
                    int cur = 0;
                    rep(l, 0, n)
                    {
                        ll sq = sqrtlw(a[l] + x);
                        if (sq * sq == a[l] + x)
                        {
                            cur++;
                        }
                    }
                    // if(cur > best){
                    //     cout << "what" << nL;
                    // }
                    best = max(best, cur);
                }
            }
        }
        int cur = 0;
        ll x = 0;
        rep(l, 0, n)
        {
            ll sq = sqrtlw(a[l] + x);
            if (sq * sq == a[l] + x)
            {
                cur++;
            }
        }
        best = max(best, cur);
        best = max(best, 1);
        if (n == 1)
        {
            best = 1;
        }
        cout << best << nL;
    }

    return 0;
}
