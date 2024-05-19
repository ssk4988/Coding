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
        int n; ll p; cin >> n >> p;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        ll ans = -1, pans = 0;
        for(ll dif = 1LL << 50; dif; dif /= 2){
            ll cur = ans + dif;
            ll cnt = 0;
            rep(i, 0, n) cnt += 1 + cur / a[i];
            if(cnt < p) ans = cur, pans = cnt;
        }
        ans++;
        int idx = -1;
        rep(i, 0, n){
            if(ans % a[i] == 0) pans++;
            if(pans == p) {
                idx = i;
                break;
            }
        }
        cout << "Case #" << (cn+1) << ": " << idx+1 << "\n";
    }
    
    return 0;
}
