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

void solve() {
    int n, k; cin >> n >> k;
    vi buf(n, -1);
    rep(i, 0, k) {
        cout << "? " << i+1 << endl;
        cin >> buf[i];
    }
    rep(i, n-k, n) {
        cout << "? " << i+1 << endl;
        cin >> buf[i];
    }
    vvi pos(2, vi(n));
    rep(i, 0, k) {
        pos[0][i] = buf[i];
        pos[1][i+n-k] = buf[i+n-k];
    }
    rep(i, k, n) {
        pos[0][i] = pos[0][i-k];
    }
    for(int i = n-k-1; i >= 0; i--) {
        pos[1][i] = pos[1][i+k];
    }
    vi diff;
    rep(i, 0, n) {
        if(i < k || i >= n-k) continue;
        if(pos[0][i] != pos[1][i]) diff.pb(i);
    }
    int lasta = k-1, firstb = n-k;
    int idx = -1;
    for(int dif = 1 << 20; dif; dif /= 2) {
        int cur = idx + dif;
        if(cur >= sz(diff)) continue;
        cout << "? " << diff[cur]+1 << endl;
        int res; cin >> res;
        if(res == pos[0][diff[cur]]) {
            idx = cur;
            lasta = max(lasta, diff[cur]);
        } else {
            firstb = min(firstb, diff[cur]);
        }
    }
    if(lasta + 1 == firstb) {
        cout << "! " << lasta+1 << " " << n-(lasta+1) << endl;
    } else cout << "! -1" << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0,nc) solve();
    
    return 0;
}
