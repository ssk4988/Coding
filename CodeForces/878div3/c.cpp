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
        int n, k; ll q; cin >> n >> k >> q;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        int l = 0, r = 0;
        ll ans = 0;
        while(l < n){
            if(a[l] > q) {
                l++; continue;
            }
            r = l;
            while(r + 1 < n && a[r + 1] <= q) r++;
            ll range = r - l + 1;
            if(range >= k){
                ans += (range - k + 1) * (range - k + 1 + 1) / 2;
            }
            l = r + 1;
        }
        cout << ans << nL;
    }
    
    return 0;
}