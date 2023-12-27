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
        int n; ll k; cin >> n >> k;
        vl a(n);
        bool above = false, below = false, eq = false;
        ll sum = 0;
        rep(i, 0, n){
            cin >> a[i];
            sum += a[i];
            if(a[i] < k) below = true;
            if(a[i] > k) above = true;
            if(a[i] == k) eq = true;
        }
        // NOT GOOD ENOUGH
        if(above && below){
            cout << -1 << nL;
            continue;
        }
        if(eq){
            bool works = true;
            rep(i, 0, n){
                if(a[i] != k) works = false;
            }
            cout << (works ? 0 : -1) << nL;
            continue;
        }
        ll g = abs(a[0] - k);
        rep(i, 1, n){
            g = __gcd(g, abs(a[i] - k));
        }
        if(g == 0){
            cout << 0 << nL;
            continue;
        }
        ll t = (k + (above ? g : -g));
        ll ans = 0;
        rep(i, 0, n){
            ans += (a[i] - t) / (t - k);
        }
        cout << ans << nL;
        // cout << ans << nL;
        // cout << g << nL;
    }
    
    return 0;
}
