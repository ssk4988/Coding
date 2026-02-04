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
    int n, m; cin >>n >> m;
    vi ord(n);
    iota(all(ord), 0);
    rep(i, 0, m) {
        int x; cin >> x; x--;
        swap(ord[x], ord[x+1]);
    }
    rep(i, 0, n) cout << ord[i]+1 << "\n" ;

    return 0;
}
