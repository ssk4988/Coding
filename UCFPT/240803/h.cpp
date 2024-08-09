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
    int n, m; cin >> n >> m;
    vi a(n), b(n);
    vvi occ(m);
    rep(i, 0, n){
        cin >> a[i]; a[i]--;
        
    }
    rep(i, 0, n){ cin >> b[i]; occ[a[i]].push_back(min(n, b[i]+1)); }
    rep(i, 0, m){
        sort(all(occ[i]));
        reverse(all(occ[i]));
    }
    int ans = -1;
    for(int dif = 1 << 20; dif; dif /= 2) {
        int cur = ans + dif;
        bool works = true;
        vi pref(n+1);
        rep(i, 0, m){
            if(sz(occ[i]) < cur){
                works = false;
                break;
            }
            rep(j, 0, cur){
                pref[occ[i][j]]++;
            }
        }
        rep(i, 1, n+1){
            pref[i] += pref[i-1];
            if(pref[i] > i){
                works = false;
            }
        }
        if(works) ans = cur;
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
