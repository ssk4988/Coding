#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,popcnt")

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

const int N = 50000;
const int Q = 5e5+10;
using bs = bitset<N>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;
    vector<bs> sets(n);
    rep(i, 0, n) {
        sets[i][i] = 1;
    }
    rep(i, 0, q){
        if(i%50 == 0) cout.flush();
        int a, b; cin >> a >> b; a--, b--;
        sets.push_back(sets[a] | sets[b]);
        cout << sets[n+i].count() << "\n";
    }
    cout.flush();
    return 0;
}
