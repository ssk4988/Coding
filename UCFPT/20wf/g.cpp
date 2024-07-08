#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vvi = vector<vi>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vl> a(n, vl(3));
    rep(i, 0, n){
        rep(j, 0, 3) cin >> a[i][j];
    }
    vl score(n);
    rep(t, 0, 2){
        vl best(8);
        rep(i, 0, n){
            rep(mask, 0, 8){
                ll cur = best[mask];
                rep(j, 0, 3){
                    cur -= a[i][j];
                    if(((mask >> j) & 1) == 0) {
                        cur += a[i][j];
                    }
                }
                score[i] = max(score[i], cur);
            }
            rep(mask, 0, 8){
                ll cur = 0;
                rep(j, 0, 3){
                    if((mask >> j) & 1) cur += a[i][j];
                }
                best[mask] = max(best[mask], cur);
            }
        }
        reverse(all(score));
        reverse(all(a));
    }
    pair<ll, ll> ans = {LLONG_MAX, -1};
    rep(i, 0, n){
        ans = min(ans, {score[i], i});
    }
    cout << ans.first << " " << (ans.second + 1) << "\n";

    return 0;
}
