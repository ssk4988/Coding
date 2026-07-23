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

    int p, v; cin >> p >> v;
    vvi idxs(20000);
    rep(i, 0, p) {
        int x, y; cin >> x >> y;
        idxs[x].push_back(i);
        idxs[y].push_back(i);
    }
    vii c(v);
    rep(i, 0, v) cin >> c[i].first, c[i].second = i;
    sort(all(c));
    vi ans(v);
    vi used(p);
    for(auto [x, idx] : c) {
        bool did = false;
        
        while(sz(idxs[x]) && used[idxs[x].back()]) idxs[x].pop_back();
        if(sz(idxs[x])) {
            ans[idx] = idxs[x].back();
            used[ans[idx]] = 1;
            did = true;
            idxs[x].pop_back();
        }
        
        if(!did) {
            cout << "impossible\n";
            return 0;
        }
    }
    for(auto x : ans) cout << x+1 << "\n";

    return 0;
}
