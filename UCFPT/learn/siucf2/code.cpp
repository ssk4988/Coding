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

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int l, n; cin >> l >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        auto test = [&](ll d) -> bool {
            int cnt = 1;
            ll cur = 0;
            for(ll x : a) {
                ll cur2 = cur + x + bool(cur);
                if(cur2 > d) {
                    cnt++;
                    cur = 0;
                }
                cur += x + bool(cur);
                if(cur > d) return false;
            }
            return cnt <= l;
        };
        ll ans = -1;
        for(ll dif = 1LL << 50; dif; dif /= 2) {
            if(!test(ans + dif)) ans += dif;
        }
        ans++;
        cout << ans << "\n";
    }

    
    return 0;
}
