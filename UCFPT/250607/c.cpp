#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

vector<vl> dijk(vector<vii> &adj, int source) {
    int n = sz(adj);
    vector<vl> dist(n);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.push({0, source});
    while(sz(pq)) {
        auto [d_u, u] = pq.top(); pq.pop();
        if(sz(dist[u]) > 2) continue;
        dist[u].push_back(d_u);
        for(auto [v, w] : adj[u]) pq.push({w+d_u, u});
    }
    return dist;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);


    return 0;
}
