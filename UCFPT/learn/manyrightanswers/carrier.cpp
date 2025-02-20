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
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vl a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        auto test = [&](ll w) {
            
            ll cur = 0;
            int ans = 1;
            rep(i, 0, n) {
                if(a[i] > w) return false;
                if(cur + a[i] > w) cur = 0, ans++;
                cur += a[i];
            }
            return ans <= k;
        };
        ll ans = -1;
        for(ll dif = 1LL << 50; dif; dif /= 2) {
            if(!test(ans + dif)) ans += dif;
        }
        ans++;
        vi bucket{0};
        ll cur = 0;
        rep(i, 0, n) {
            if(a[i] + cur > ans) bucket.pb(0), cur = 0;
            bucket.back()++;
            cur += a[i];
        }
        while(sz(bucket) < k) bucket.pb(0);
        rep(i, 0, k) cout << bucket[i] << "\n";
    }
    
    
    return 0;
}
