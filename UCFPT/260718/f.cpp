#include <bits/stdc++.h>
using namespace std;

// using ll = long long;
using ll = __int128_t;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

string to128(ll x) {
    if(x == 0) return "0"s;
    string res;
    while(x) {
        res += '0' + (x % 10);
        x /= 10;
    }
    reverse(all(res));
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    n += m;
    vector<vi> child(n);
    vl pedge(n);
    rep(i, 1, n) {
        int p, c; cin >> p >> c;
        p--;
        child[p].push_back(i);
        pedge[i] = c;
    }
    vl slopeat0(n), yint(n);
    vector<multiset<ll>> slopes(n);
    for(int u = n-1; u >= 0; u--) {
        // merge children
        for(int v : child[u]) {
            slopeat0[u] += slopeat0[v];
            for(auto x : slopes[v]) slopes[u].insert(x);
            slopes[v] = multiset<ll>();
            yint[u] += yint[v];
        }
        // cerr << "u: " << u << " slope " << slopeat0[u] << " y=" << yint[u] << " pedge " << pedge[u] << " slopes: ";
        // for(auto x : slopes[u]) cerr << x << ",";
        // cerr << " children: ";
        // for(auto v : child[u]) cerr << v << ",";
        // cerr << endl;
        // extend leaf
        if(u + m >= n) {
            slopes[u].insert(pedge[u]);
            slopes[u].insert(pedge[u]);
            slopeat0[u] = -1;
            yint[u] = pedge[u];
        } else {
            // extend junction
            multiset<ll> ns;
            for(auto x : slopes[u]) ns.insert(x + pedge[u]);
            slopes[u] = ns;
            yint[u] -= slopeat0[u] * pedge[u];
            while(sz(slopes[u]) > 2) {
                auto p = *begin(slopes[u]);
                yint[u] -= p;
                slopeat0[u]++;
                slopes[u].erase(slopes[u].find(p));
                slopes[u].erase(prev(end(slopes[u])));
            }
        }
        // cerr << "u: " << u << " slope " << slopeat0[u] << " y=" << yint[u] << " pedge " << pedge[u] << " slopes: ";
        // for(auto x : slopes[u]) cerr << x << ",";
        // cerr << " children: ";
        // for(auto v : child[u]) cerr << v << ",";
        // cerr << endl;
    }
    assert(sz(slopes[0]) == 2);
    ll ans = yint[0] + slopeat0[0] * *begin(slopes[0]);
    cout << to128(ans) << "\n";

    return 0;
}
