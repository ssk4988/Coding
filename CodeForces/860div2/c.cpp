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
    int nc; cin >> nc;

    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n), b(n);
        rep(i, 0, n){
            cin >> a[i] >> b[i];
        }
        int r = 0;
        int ans = 0;
        ll lc = 0, gc = 0;
        while(r < n){
            ans++;
            gc = b[r] * a[r];
            lc = b[r++];
            while(r < n){
                lc = lc / gcd(lc, b[r]) * b[r];
                gc = gcd(gc, a[r] * b[r]);
                if(gc % lc == 0){
                    r++;
                }
                else{
                    break;
                }
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
