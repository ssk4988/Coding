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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        ll pre = 0;
        set<ll> ss;
        ll ans = 0;
        ll mx = 0;
        rep(i, 0, n) {
            cin >> a[i];
            if(i == 0) pre = a[i];
            ll dif = max(0LL, pre - a[i]);
            ss.insert(dif);
            mx = max(mx, dif);
            ans += dif;
            pre = max(pre, a[i]);
        }
        cout << (ans + mx) << "\n";
    }
    
    return 0;
}
