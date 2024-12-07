#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    ll ans = -1;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    for(ll dif = 1LL << 35; dif; dif /= 2) {
        ll cur = ans + dif;
        int cnt = 0;
        ll prv = -1e18;
        rep(i, 0, n){
            if(abs(a[i] - prv) <= cur) continue;
            cnt++;
            prv = a[i] + cur;
        }
        // cout << ans << " " << cnt << endl;
        if(cnt > k) ans = cur;
    }
    ans++;
    cout << ans << "\n";
    
    return 0;
}
