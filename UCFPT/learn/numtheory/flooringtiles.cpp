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
    vl ans(76);
    auto isprime = [](int v) -> bool
    {
        rep(i, 2, v)
        {
            int o = (v + i - 1) / i;
            if (i > o)
                break;
            if (v % i == 0)
                return false;
        }
        return true;
    };
    vl primes;
    for (int i = 2; sz(primes) < 80; i++)
    {
        if (isprime(i))
            primes.pb(i);
    }
    // cout << primes.back() << nL;
    // for(int i : primes){
    //     cout << i << nL;
    // }
    ll lim = 1e18;
    rep(i, 1, 76)
    {
        auto solve = [&](int left, int pidx, int prevp, ll cur, auto &&solve) -> ll
        {
            if(left == 1) return 1;
            ll ans = LLONG_MAX;
            ll margin = lim / cur;
            rep(i, 2, prevp + 1)
            {
                if (left % i != 0)
                    continue;
                ll mult = 1;
                bool works = true;
                ll ov = (lim + primes[pidx] - 1) / primes[pidx];
                rep(j, 0, i - 1)
                {
                    if(mult > ov){
                        works = false;
                        break;
                    }
                    mult *= primes[pidx];
                }
                if(!works) continue;
                if(mult > margin) continue;
                ll res = solve(left / i, pidx + 1, i, mult * cur, solve);
                if(res == LLONG_MAX) continue;
                ans = min(ans, mult * res);
            }
            return ans;
        };
        // ans[i] = solve()
        ans[i] = LLONG_MAX;
        ans[i] = min(ans[i], solve(i * 2, 0, i * 2, 1, solve));
        if (i > 1)
        {
            ans[i] = min(ans[i], solve(i * 2 - 1, 0, i * 2 - 1, 1, solve));
        }
        if (i == 1)
            ans[i] = 1;
        // cout << i << " " << ans[i] << nL;
    }
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        cout << ans[n] << nL;
    }

    return 0;
}
