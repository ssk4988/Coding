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
        vi a(n), ans(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n){
            int lo = 0, hi = i;
            while(lo < hi){
                int mid = lo + (hi - lo) / 2;
                int len = i - mid + 1;
                if(a[mid] >= len){
                    hi = mid;
                }
                else{
                    lo = mid + 1;
                }
            }
            ans[i] = i - lo + 1;
        }
        rep(i, 0, n){
            cout << ans[i] << (i + 1 < n ? " " : "\n");
        }
    }
    
    return 0;
}
