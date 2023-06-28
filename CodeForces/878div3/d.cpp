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
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        set<ll> ss;
        rep(i, 0, n) ss.insert(a[i]);
        a.clear();
        for(ll i : ss) a.pb(i);
        n = sz(a);
        if(n <= 3){
            cout << "0\n";
            continue;
        }
        ll ans = LLONG_MAX;
        int r = 0;
        rep(i, 0, n - 2){
            ll leftwait = (a[i] - a[0] + 1) / 2;
            r = max(r, i + 1);
            while(r + 2 < n && (a[r + 1] - a[i + 1] + 1) / 2 <= (a[n - 1] - a[r + 2] + 1) / 2){
                r++;
            }
            ll rightwait = max((a[r] - a[i + 1] + 1) / 2, (a[n - 1] - a[r + 1] + 1) / 2);
            if(r + 1 + 1 < n){
                rightwait = min(rightwait, max((a[r + 1] - a[i + 1] + 1) / 2, (a[n - 1] - a[r + 1 + 1] + 1) / 2));
            }
            ans = min(ans, max(leftwait, rightwait));
        }
        cout << ans << nL;
    }
    
    return 0;
}
