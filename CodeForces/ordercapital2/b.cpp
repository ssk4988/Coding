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
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vi b(n);
        rep(i, 0, n) cin >> b[i];
        vi ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) { return a[i] < a[j]; });
        bool works = true;
        rep(i, 0, n) {
            if(a[ord[i]] > b[i]) works = false;
        }
        if(!works) {
            cout << "-1\n";
            continue;
        }
        for(int i = n-1; i >= 0; i--) {
            rep(j, 0, n-1) {
                if(max(a[ord[j]], a[ord[j+1]]) <= min(b[j+1], b[j]) && ord[j] > ord[j+1]) {
                    swap(ord[j], ord[j+1]);
                }
            }
        }
        int ans = 0;
        vi inv(n);
        rep(i, 0, n) inv[ord[i]] = i;
        rep(i, 0, n) {
            rep(j, 0, i) if(inv[j] > inv[i]) ans++;
        }
        cout << ans << "\n";
        // rep(i, 0, n) cout << ord[i] << "-" << a[ord[i]] << " ";
        // cout << "\n";
    }
    // 3 2 4 1
    return 0;
}
