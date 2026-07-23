#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vvi child(n);

    vl a(k);
    rep(i, 0, k) cin >> a[i];
    sort(all(a));
    reverse(all(a));
    vi used(n);
    vii deepest(n);
    vi p(n, -1);
    rep(i, 1, n) {
        cin >> p[i];
        child[p[i]].push_back(i);
    }
    for(int i = n-1; i >= 0; i--) {
        deepest[i] = {0, i};
        for(int j : child[i]) {
            pii cand = deepest[j];
            cand.first++;
            deepest[i] = max(deepest[i], cand);
        }
    }
    set<pii> q;
    for(int c : child[0]) q.insert({deepest[c].first, c});
    ll ans = 0;
    rep(i, 0, k) {
        auto [dep, r] = *rbegin(q);
        q.erase(prev(end(q)));
        auto [dep2, l] = deepest[r];
        while(l != r) {
            // cerr << "at " << l << " add " << a[i] << endl;
            used[l] = 1;
            ans += a[i];
            l = p[l];
            for(int v : child[l]) if(!used[v]) q.insert({deepest[v].first, v});
        }
        ans += a[i];
        used[l] = 1;
    }
    cout << ans << "\n";

    return 0;
}
