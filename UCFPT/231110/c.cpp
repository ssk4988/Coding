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
const ll MOD = 1e9 + 7;
struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif){
        for(; pos < sz(s); pos |= pos + 1){ 
            s[pos] += dif;
            if(s[pos] >= MOD) s[pos] -= MOD;
        }
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos - 1];
        res %= MOD;
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vii a(n);
        set<int> ss;
        rep(i, 0, n){
            cin >> a[i].first;
            a[i].second = i + 1;
            ss.insert(a[i].first);
        }
        ss.insert(0);
        map<int, int> rl;
        for(int i : ss) rl[i] = sz(rl);
        n++;
        sort(all(a), [](pii a, pii b)-> bool {
            if(a.first == b.first) return a.second > b.second;
            return a.first < b.first;
        });
        vector<FT> fts(m + 1, FT(n + 5));
        // rep(i, 0, m+1) fts[i] = FT(n + 5);
        fts[0].update(0, 1);
        for(auto [v, idx] : a){
            int v1 = rl[v];
            for(int i = m; i > 0 ;i--){
                fts[i].update(idx, fts[i - 1].query(idx));
            }
        }
        ll ans = fts[m].query(n + 5);
        cout << "Case #" << (cn + 1) << ": " << ans << "\n";
    }
    return 0;
}
