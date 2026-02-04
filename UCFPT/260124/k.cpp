#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    if(n * m % k != 0) {
        cout << "impossible\n";
        return 0;
    }
    int x = -1;
    rep(i, 1, n+1) {
        if(k % (n/i) == 0 && n % i == 0 && m % (k/(n/i)) == 0) {
            x = i;
        }
    }
    int y = m / (k/(n/x));
    cerr << x << " " << y << endl;
    rep(i, 0, n) {
        rep(j, 0, m) {
            int c = (i/x) * (m/y) + j/y;
            cout << char('A'+c);
        }
        cout << "\n";
    }

    return 0;
}
