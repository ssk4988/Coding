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
    ll n;
    cin >> n;
    double best_dif = 0;
    double best_casino = 1;
    ll w = 0, b = n, r = 0;
    ll b1, w1, r1;
    for(ll i = 0; i <= n; i++)
    {
        b1 = n - i;
        ll t1 = sqrt(n * n - (i * i));
        if (t1 * t1 + i * i == n * n)
        {
            w1 = n - t1;
            r1 = n - w1 - b1;
            // cout << b1 << " " << w1 << " " << r1 << nL;
            if (w1 < 0 || r1 < 0 || b1 < 0)
                continue;
            w = w1, r = r1, b = b1;
            if (b1 < w1)
                break;
        }

    }
    cout << 2 << nL;
    cout << b << " " << w << nL;

    return 0;
}