#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        if(gcd(n, m) > 1) {
            cout << "No\n";
            continue;
        }
        // bool sw = n > m;
        // if(sw) {
        //     swap(n, m);
        // }
        vi a(n);
        a[0] = 1;
        rep(i, 1, sz(a)) {
            a[i] = a[i-1] + m;
        }
        vi b(m);
        b[0] = 1;
        rep(i, 1, sz(b)) {
            b[i] = b[i-1] + n;
            b[i] %= n * m;
        }
        // if(sw) swap(a, b);
        cout << "Yes\n";
        for(auto x : a) cout << x%(n*m) << " ";
        cout << "\n";
        for(auto x : b) cout << x%(n*m) << " ";
        cout << "\n";
    }

    return 0;
}
