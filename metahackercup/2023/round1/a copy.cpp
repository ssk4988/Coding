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
        vl x(n);
        rep(i, 0, n){
            cin >> x[i];
        }
        sort(all(x));
        vd leftdist(n), rightdist(n);
        // ll running = x[1] - x[0];
        // // ll mididx = 0;
        // leftdist[1] = ld(x[0] + x[1]) / 2;
        rep(i, 1, n){
            // running += x[i] - x[mididx];
            // while(mididx + 1 < n && i - mididx >= mididx + 1){
            //     running -= ((i - mididx) - (mididx + 1)) * (x[mididx + 1] - x[mididx]);
            //     mididx++;
            // }
            leftdist[i] = ld(x[0] + x[i]) / 2;
            // leftdist[i] = mididx;
        }
        // running = x[n - 1] - x[n - 2];
        // mididx = n - 1;
        // rightdist[n - 2] = n - 2;
        for(int i = n - 2; i >= 0; i--){
            // running += x[mididx] - x[i];
            // while(mididx > 0 && mididx - i >= n - mididx){
            //     running -= ((mididx - i) - (n - mididx)) * (x[mididx] - x[mididx - 1]);
            //     mididx--;
            // }
            // rightdist[i] = mididx;
            rightdist[i] = ld(x[n - 1] + x[i]) / 2;
        }
        ld ans = 1e15;
        rep(i, 1, n - 2){
            ans = min(ans, -leftdist[i] + rightdist[i + 1]);
        }
        cout << fixed << setprecision(8) << ans << "\n";
    }
    
    return 0;
}
