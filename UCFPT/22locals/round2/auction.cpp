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

// f(x) = p * x / (x + v)
// d(x) = f(x + 1) - f(x) = p * ((x + 1) / (x + v + 1) - x / (x + v)) = p *
// x^2+xv+x+v - x^2-xv-x =
// d(x) = p * v / (x + v)(x + v + 1)
// find largest x such that d(x) >= k

vi p, v;
int n, votes;
ld eps = 1e-10;


// gives the derivative/additional benefit for item i if there are x votes and we add 1 more
ld d(int i, ll x)
{
    ld denom = x + v[i];
    return (ld)(v[i]) * p[i] / denom / (denom + 1);
}

// profit function
ld prof(int i, ll x){
    return (ld)p[i] * x / (x + v[i]);
}


// find how many of our votes needed before decreasing returns fall under k
ll numv(int i, ld minder)
{
    ll lo = 0, hi = votes;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo + 1) / 2;
        ld deriv = d(i, mid);
        if (deriv >= minder)
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

ll totv(ld minder)
{
    ll ans = 0;
    rep(i, 0, n)
    {
        ans += numv(i, minder);
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> votes;
    p.resize(n);
    v.resize(n);
    rep(i, 0, n)
    {
        cin >> p[i] >> v[i];
    }
    ld lo = 0, hi = 1000;//1e10;
    while (abs(lo - hi) > eps)
    {
        ld mid = (lo + hi) / 2;
        ll vnum = totv(mid);
        if (vnum < votes)
        {
            hi = mid;
        }
        else if(vnum == votes){
            lo = hi = mid;
        }
        else{
            lo = mid;
        }
    }
    ld ans = 0;
    ll left = votes;
    rep(i, 0, n){
        ll thisv = min(left, numv(i, lo));
        left -= thisv;
        ans += prof(i, thisv);
    }
    cout << ans << nL;
    // cout << totv(lo) << nL;

    return 0;
}
