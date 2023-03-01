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

vector<ld> e, prob;
int n;
vector<ld> p;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    p = vector<ld>(n);
    rep(i, 0, n)
    {
        cin >> p[i];
    }
    e = vector<ld>(1 << n, -1);
    prob = vector<ld>(1 << n, 0);
    prob[(1 << n) - 1] = 1;
    e[(1 << n) - 1] = 0;
    auto transtot = [&](int bitmask) -> ld
    {
        ld invprod = 1, prod = 1;
        rep(i, 0, n)
        {
            if ((1 << i) & bitmask)
            {
                invprod *= 1 - p[i];
                prod *= p[i];
            }
        }
        ld res = 0;
        rep(i, 0, n)
        {
            if ((1 << i) & bitmask)
            {
                res += invprod / (1 - p[i]) * p[i];
                res += prod / p[i] * (1 - p[i]);
            }
        }
        return res;
    };
    auto trans = [&](int bitmask, int bit) -> ld
    {
        ld invprod = 1, prod = 1;
        rep(i, 0, n)
        {
            if ((1 << i) & bitmask)
            {
                if (bit == i)
                {
                    invprod *= p[i];
                    prod *= 1 - p[i];
                }
                else
                {
                    invprod *= 1 - p[i];
                    prod *= p[i];
                }
            }
        }
        return invprod + prod;
    };
    auto solve = [&](int bitmask, auto &&solve) -> void
    {
        if (e[bitmask] >= 0)
            return;
        e[bitmask] = 0;
        rep(i, 0, n)
        {
            if ((1 << i) & bitmask)
                continue;
            int b1 = bitmask | (1 << i);
            solve(b1, solve);
            ld tt = transtot(b1);
            ld probpiece = prob[b1] * trans(b1, i) / tt;
            prob[bitmask] += probpiece;
            e[bitmask] += probpiece * (e[b1] + 1 / tt);
        }
        e[bitmask] /= prob[bitmask];
    };
    ld psum = 0, esum = 0;
    rep(i, 0, 1 << n){
        if(__builtin_popcount(i) >= 2){
            solve(i, solve);
            if(__builtin_popcount(i) == 2){
                psum += prob[i];
                esum += e[i] * prob[i];
            }
        }
    }
    esum /= psum;
    cout << fixed << setprecision(8) << esum << nL;

    return 0;
}
