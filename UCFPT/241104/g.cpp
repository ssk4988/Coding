#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using ll = long long int;
using vl = vector<ll>;
using ld = long double;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T> & V): jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;

    vector<pair<string, int>> s(n);
    vi lcp(n);
    rep(i, 0, n){
        cin >> s[i].first;
        s[i].second = i;
    }
    sort(all(s));

    rep(i, 1, n){
        while(lcp[i] < min(sz(s[i].first), sz(s[i-1].first)) && s[i].first[lcp[i]] == s[i-1].first[lcp[i]]) lcp[i]++;
    }
    vi inv(n);
    rep(i, 0, n) inv[s[i].second] = i;
    RMQ rmq(lcp);
    

    while(q--) {
        int k; cin >> k;
        vi sub(k);
        rep(i, 0, k) cin >> sub[i];

        sort(all(sub), [&](int i, int j) { return inv[i] < inv[j]; });

        vi bits;
        rep(i, 0, k-1) bits.push_back(rmq.query(inv[sub[i]]+1, inv[sub[i+1]]+1));

        sort(all(bits));
        bits.erase(unique(all(bits)), end(bits));

        cout << sz(bits) << ' ';
        for(int b: bits) cout << b << ' ';
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    rep(i, 0, t) {
        cout << "Case #" << i+1 << ":\n";
        solve();
    }

    return 0;
}