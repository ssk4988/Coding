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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, d;
        cin >> n >> d;
        using pp = pair<ld, pi>;
        vector<pp> a(d);
        rep(i, 0, d)
        {
            cin >> a[i].s.f >> a[i].f >> a[i].s.s;
        }
        vi v(n);
        int mx = 0;
        rep(i, 0, n) { 
            cin >> v[i];
            mx = max(mx, v[i]);
        }
        vd sc(d, LDBL_MAX);
        int best = 0;
        rep(i, 0, d)
        {
            if(a[i].s.s < mx) continue;
            int boxes = 0, left = 0, ds = 0;
            rep(j, 0, n)
            {
                if(left < v[j]){
                    ds++;
                    left = a[i].s.s;
                }
                left -= v[j];
            }
            boxes = (ds + (a[i].s.f - 1)) / a[i].s.f;
            sc[i] = boxes * a[i].f;
            if(sc[i] < sc[best]) best = i;
        }
        cout << "Diaper Scenario #" << (cn + 1) << ": Buying box " << (best + 1) << ", you spend $" << fixed << setprecision(2) << sc[best] << ".\n";
    }

    return 0;
}
