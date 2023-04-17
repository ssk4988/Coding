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
    int MAXN = 2e5 + 20;
    vvi idx(2 * MAXN);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
        idx[a[i] * 2 + (i % 2)].pb(i);
    }
    ll ans = 0;
    rep(i, 0, sz(idx)){
        if(sz(idx[i]) == 0) continue;
        int l = 0, r = 0, match = 0;
        for(int cur : idx[i]){
            int maxmid = min(n - 1 - k/2, cur + k/2), minmid = max(0 + k/2, cur);
            if(maxmid < minmid) continue;
            int leftcheck = minmid + (minmid - cur), rightcheck = maxmid + (maxmid - cur);
            while(r < sz(idx[i]) && idx[i][r] <= rightcheck){
                r++;
            }
            while(r > 0 && idx[i][r - 1] > rightcheck) r--;
            while(l < sz(idx[i]) && idx[i][l] < leftcheck){
                l++;
            }
            while(l > 0 && idx[i][l - 1] >= leftcheck) l--;
            ans += (rightcheck - leftcheck) / 2 + 1 - (r - l);
        }
    }
    cout << ans << nL;

    
    return 0;
}
