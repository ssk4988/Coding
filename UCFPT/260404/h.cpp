#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];

    vii ord;
    rep(i, 0, n) {
        ord.emplace_back(a[i], i);
    }
    sort(all(ord), greater<pii>());

    Tree<int> idxs;
    rep(i, 0, n) idxs.insert(i);

    map<int, vi> rem;
    rep(i, 0, n)
        rem[a[i]].push_back(i);

    ll res = 0;
    for(auto [x, i]: ord) {
        for(int j: rem[x]) {
            idxs.erase(j);
        }
        rem[x] = vi();

        auto it = idxs.lower_bound(i);
        if(it == end(idxs)) continue;
        int left = idxs.order_of_key(*it);
        int right = sz(idxs) - left;
        res += min(left, right);
    }

    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}
 