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

struct Line
{
    mutable ll k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>>
{
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b)
    { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if (y == end())
            return x->p = inf, 0;
        if (x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m)
    {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
bool DEBUG = false;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, c, d;
    int cn = 1;
    while(true){
        cin >> n >> c >> d;
        if(n == 0 && c == 0 && d == 0) break;
        vector<vl> a(n, vl(4));
        rep(i, 0, n){
            rep(j, 0, 4){
                cin >> a[i][j];
            }
        }
        sort(all(a));
        vi days;
        days.pb(0);
        rep(i, 0, n){
            if(days.size() == 0 || days.back() != a[i][0]){
                days.pb(a[i][0]);
            }
        }
        // if(days.back() != d) days.pb(d)
        days.pb(d + 1);
        vl dp(days.size());
        LineContainer lc;
        lc.add(0, c);
        // break ties by day? - dp on day, not machine, coordinate compress
        // not enough money? - don't add if not enough money
        int pnt = 0;
        rep(i, 0, sz(dp)){
            // day buy sell profit-rate
            dp[i] = lc.query(days[i]);
            while(pnt < n && a[pnt][0] == days[i]){
                if(dp[i] >= a[pnt][1]) lc.add(a[pnt][3], dp[i] + a[pnt][2] - a[pnt][1] - a[pnt][3] * (a[pnt][0] + 1));
                else{
                    if(DEBUG) cout << "cant afford machine " << pnt << " which costs " << a[pnt][1] << " while having " << dp[i] << nL;
                }
                pnt++;
            }
        }
        cout << "Case " << cn << ": " << dp.back() << nL;
        cn++;
    }

    
    return 0;
}
