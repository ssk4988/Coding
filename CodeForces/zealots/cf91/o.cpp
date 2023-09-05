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
using vvl = vector<vl>;

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
    ll n, m, k;
    cin >> n >> m >> k;
    vl a(n), b(m);
    vl reva(2 * max(n, m), -1), revb(2 * max(n, m), -1);
    rep(i, 0, n)
    {
        cin >> a[i];
        a[i]--;
        reva[a[i]] = i;
    }
    ll g = gcd(n, m);
    ll lc = n / g * m;
    rep(i, 0, m)
    {
        cin >> b[i];
        b[i]--;
        revb[b[i]] = i;
    }
    if (n < m)
    {
        swap(n, m);
        swap(a, b);
        swap(reva, revb);
    }
    // m < n, b < a
    vvl residue(g);
    vl revres(n);
    rep(i, 0, g)
    {
        residue[i].pb(i);
        int cur = (i + m) % n;
        while (cur != i)
        {
            residue[i].pb(cur);
            cur = (cur + m) % n;
        }
        rep(j, 0, sz(residue[i]))
        {
            revres[residue[i][j]] = j;
        }
    }
    vl timeofoverlap(m, -1);
    int overlapcycle = 0;
    rep(i, 0, m)
    {
        if ((reva[b[i]] == -1 || reva[b[i]] % g != revb[b[i]] % g))
        {
            continue;
        }
        int ind = revres[reva[b[i]]];
        int ind1 = revres[revb[b[i]]];
        if (ind < ind1)
            ind += sz(residue[revb[b[i]] % g]);
        timeofoverlap[i] = (ind - ind1) * m + i;
        timeofoverlap[i]++;
        overlapcycle++;
    }
    overlapcycle = lc - overlapcycle;
    ll lo = 0, hi = 1'000'000'000'000'000'100LL;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;
        ll lccyles = mid / lc;
        ll cur = lccyles * overlapcycle;
        cur += mid % lc;
        rep(i, 0, m)
        {
            if (timeofoverlap[i] != -1 && mid % lc >= timeofoverlap[i])
            {
                cur--;
            }
        }
        // cout << mid << " yields " << cur << nL;
        if (cur >= k)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << lo << nL;

    return 0;
}
