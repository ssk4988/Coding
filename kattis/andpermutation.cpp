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
    int n; cin >> n;
    vl a(n);
    vll ord(n);
    rep(i, 0, n){
        cin >> a[i];
        ord[i].f = a[i];
        ord[i].s = i;
    }
    sort(all(ord));
    sort(all(a));
    vl b(a);
    rep(k, 0, 60) {
        rep(i, 0, n){
            if(!((a[i] >> k) & 1)) continue;
            int j = lower_bound(all(a), a[i] ^ (1LL << k)) - begin(a);
            swap(b[j], b[i]);
        }
    }
    vl ans(n);
    rep(i, 0, n) ans[ord[i].s] = b[i];
    rep(i, 0, n) cout << ans[i] << "\n";

    return 0;
}
