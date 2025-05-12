#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long double> qpow(m+1, 1);
    rep(i, 0, n)
        qpow[i+1] = qpow[i] / 4.0;

    vector<long double> min_exp(n, 1e9), sum_exp(n), cnt(n), init_exp(n), exp(n, 1e9);
    exp[n-1] = min_exp[n-1] = 0;

    using state = pair<long double, int>;
    priority_queue<state, vector<state>, greater<>> pq;
    pq.emplace(0.0, n-1);
    vi seen(n);

    while(!pq.empty()) {
        auto [E, u] = pq.top(); pq.pop();
        if(E < exp[u]) continue;
        seen[u] = 1;

        for(int v: adj[u]) if(!seen[v]) {
            min_exp[v] = min(min_exp[v], exp[u]);
            sum_exp[v] += qpow[cnt[v]] * 0.75L * (E + cnt[v] + 1);
            cnt[v]++;
            init_exp[v] = qpow[cnt[v]] * (2 + min_exp[v] + cnt[v]);
            exp[v] = init_exp[v] + sum_exp[v];
            pq.emplace(exp[v], v);
        }
    }

    cout << setprecision(20) << fixed << exp[0] << '\n';

    return 0;
}
