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
    int ninf = -1e7;
    rep(cn, 0, nc){
        int n, k, d, w; cin >> n >> k >> d >> w;
        int cur = ninf;
        int ans = 0;
        int dosesleft = 0;
        vi t(n);
        rep(i, 0, n){
            cin >> t[i];
        }
        int pnt = 0;
        while(pnt < n){
            int cur = t[pnt] + w;
            ans++;
            dosesleft = k;
            while(pnt < n && dosesleft > 0){
                if(t[pnt] + w >= cur && t[pnt] <= cur + d){
                    pnt++;
                    dosesleft--;
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
