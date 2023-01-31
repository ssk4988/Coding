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

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

vl x, y, a, xbest, ybest, maxv, minv;
int n;
ll s; 
ll minscore = LLONG_MAX;

ll calcscore(vl &cx, vl &cy)
{
    ll sum = 0;
    rep(i, 0, n - 1)
    {
        sum += cy[i] * cx[i + 1];
    }
    return sum;
}

void solve(int idx, vl &cx, vl &cy)
{
    if (idx == n - 1)
    {
        ll c = calcscore(cx, cy);
        if (c < minscore)
        {
            minscore = c;
            xbest = vl(cx);
            ybest = vl(cy);
        }
        return;
    }
    ll minv = LLONG_MIN, maxv = LLONG_MAX;
    if (a[idx] == 2 * s)
    {
        minv = s;
        maxv = s;
    }
    else if (a[idx] < 2 * s)
    {
        maxv = min(a[idx], s);
        minv = a[idx] - maxv;
    }
    else
    {
        minv = max(s, (ll)0);
        maxv = a[idx] - s;
    }
    for (int i = minv; i <= maxv; i++)
    {
        cy[idx] = i;
        cx[idx] = a[idx] - cy[idx];
        solve(idx + 1, cx, cy);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> s;
    a.resize(n);
    x.resize(n);
    y.resize(n);
    maxv.resize(n);
    minv.resize(n);
    rep(i, 0, n)
    {
        cin >> a[i];
        if(i == 0 || i == n - 1) continue;
        if (a[i] == 2 * s)
        {
            minv[i] = s;
            maxv[i] = s;
        }
        else if (a[i] < 2 * s)
        {
            maxv[i] = min(a[i], s);
            minv[i] = a[i] - maxv[i];
        }
        else
        {
            minv[i] = max(s, (ll)0);
            maxv[i] = a[i] - minv[i];
        }
    }
    y[0] = a[0];
    x[n - 1] = a[n - 1];
    solve(1, x, y);
    rep(i, 0, n)
    {
        cout << xbest[i] << " ";
    }
    cout << "x" << nL;
    rep(i, 0, n)
    {
        cout << ybest[i] << " ";
    }
    cout << "y" << nL;
    rep(i, 0, n)
    {
        cout << minv[i] << " ";
    }
    cout << "min" << nL;
    rep(i, 0, n)
    {
        cout << maxv[i] << " ";
    }
    cout << "max" << nL;
    cout << minscore << nL;
    return 0;
}
