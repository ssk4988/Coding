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
        int m, k, a1, ak; cin >> m >> k >> a1 >> ak;
        int nk = m / k, n1 = m % k;
        int ans = INT_MAX;
        // ans = min(ans, )
        int mk = m / k * k;
        if(ak >= mk){
            ans = max(0, n1 - a1);
        }
        else{
            int usedk = mk - ak;
            m -= ak * k;
            ans = min(ans, max(0, m - a1));
            int left = m - a1;
            if(left > 0){
                int rr = (left + k - 1) / k * k;
                if(rr > m){
                    ans = min(ans, left / k + left % k);
                }
                else ans = min(ans, rr / k + max(0, m - rr - a1));
            }

        }
        // if(nk <= ak){
        //     cout << max(0, n1 - a1) << nL;
        // }
        // else{
        //     int left = m - ak * k - a1;
            
        //     cout << min((left + k - 1) / k, ) << nL;
        // }
        cout << ans << nL;
    }
    
    return 0;
}
