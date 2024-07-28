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
    int n; cin >> n;
    vl a(n), b(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, n) cin >> b[i];
    ll from = a[0] - b[0];
    vl pos, neg;
    ll ans = 0;
    rep(i, 1, n){
        if (from > 0) pos.pb(from);
        if (from < 0) neg.pb(abs(from));
        ans += abs(from);
        from += a[i] - b[i];
    }
    sort(all(pos));
    reverse(all(pos));
    sort(all(neg));
    reverse(all(neg));
    vector<vl> vs = {pos, neg};
    for(vl &v : vs)
    {
        ll pre = 0;
        while(sz(v) && sz(v) > n - sz(v)) {
            ll dif = v.back() - pre;
            ans -= dif * (sz(v) - (n - sz(v)));
            pre = v.back();
            v.pop_back();
        }
    }
    cout << ans << "\n";


    
    return 0;
}
