#include <bits/stdc++.h>
using namespace std;

#define int long long
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


signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, k; cin >> n >> m >> k;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi d(m), f(k);
        rep(i, 0, m) cin >> d[i];
        rep(i, 0, k) cin >> f[i];
        sort(all(d));
        sort(all(f));
        reverse(all(f));
        int mxdif = 0;
        rep(i, 0, n-1) mxdif = max(a[i+1] - a[i], mxdif);
        int occ = 0;
        rep(i, 0, n-1){
            if(a[i+1] - a[i] == mxdif) occ++;
        }
        if(occ > 1){
            cout << mxdif << "\n";
            continue;
        }
        pi snd = {0, -1};
        rep(i, 0, n-1){
            if(a[i+1] - a[i] == mxdif) occ = i;
            if(a[i+1] - a[i] < mxdif) snd = max(snd, {a[i+1] - a[i], i});
        }
        int l = a[occ], r = a[occ + 1], mid = (l + r) / 2;
        int p = 0;
        int ans = mxdif;
        rep(i, 0, m){
            while(p < k && d[i] + f[p] > mid) p++;
            if(p < k && d[i] + f[p] >= l && d[i] + f[p] <= r) ans = min(ans, max({snd.f, d[i] + f[p] - l, r - (d[i] + f[p])}));
            if(p - 1 >= 0 && d[i] + f[p-1] >= l && d[i] + f[p-1] <= r) ans = min(ans, max({snd.f, d[i] + f[p-1] - l, r - (d[i] + f[p-1])}));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
