#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    freopen("cubes.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n), b(n);
        rep(i, 0, n) cin >> a[i];
        sort(all(a));
        reverse(all(a));
        rep(i, 0, n){
            if(i % 2 == 1) b[i / 2] = a[i];
            else b[n - 1 - i / 2] = a[i];
        }
        cout << "Case " << (cn + 1) << ":\n";
        rep(i, 0, n) cout << b[i] << (i + 1 < n ? " " : "");
        cout << "\n";
    }
}
