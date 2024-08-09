#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

void solve() {
    ll n; cin >> n;
    auto solve = [&](vi x) -> ll {
        ll ans = 0;
        rep(i, 0, n){
            if(x[i] == n/2){
                for(int j = i; j > 0; j--){
                    swap(x[j], x[j-1]);
                    ans++;
                }
            }
        }
        rep(i, 0, n){
            if(x[i] == n/2 + 1){
                for(int j = i; j + 1 < n; j++){
                    swap(x[j], x[j+1]);
                    ans++;
                }
            }
        }
        vi cnt(2), expect = {1, 0};
        rep(i, 1, n-1){
            int t = x[i] > n/2;
            if(cnt[1-t] > expect[t]) ans += cnt[1-t] - expect[t];
            cnt[t]++;
            expect[t]++;
        }
        return ans;
    };
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    ll ans = solve(a);
    rep(i, 0, n) a[i] = n + 1 - a[i];
    ans = min(ans, solve(a));
    cout << (n/2 * (n-1) + (n-1)/2) << " " << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
