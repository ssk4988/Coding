#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvii = vector<vii>;
using tlll = tuple<ll, ll, ll>;
using vlll = vector<tlll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

vector<ll> dijkstras(vvii &adj, int s) {
    vector<ll> dist(sz(adj), 1e15);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.emplace(0, s);
    while(!pq.empty()) {
        auto [d, cur] = pq.top(); pq.pop();
        if(d > dist[cur]) continue;
        for(auto [nxt, wt]: adj[cur]) {
            int nxtD = d + wt;
            if(nxtD >= dist[nxt]) continue;
            dist[nxt] = nxtD;
            pq.emplace(nxtD, nxt);
        }
    }
    return dist;
}

int mx;

void cc(vlll &list) {
    vector<ll> vals;
    for(auto [v1, v2, v3]: list)
        vals.push_back(v1), vals.push_back(v2), vals.push_back(v3);
    
    sort(all(vals));
    vals.erase(unique(all(vals)), end(vals));
    mx = sz(vals);

    auto change = [&](ll &v) -> void {
        v = lower_bound(all(vals), v) - begin(vals);
    };

    for(auto &[v1, v2, v3]: list)
        change(v1), change(v2), change(v3);
}

const int inf = 1e9;
struct node {
    int lo, md, hi;
    int minVal = inf;
    node *left, *right;
    node(int L, int R): lo(L), md((L+R)>>1), hi(R) {
        if(lo == hi) return;
        left = new node(lo, md);
        right = new node(md+1, hi);
    }
    void update(int idx, int val) {
        if(lo == hi) return void(minVal = min(minVal, val));
        if(idx <= md) left->update(idx, val);
        else right->update(idx, val);
        minVal = min(left->minVal, right->minVal);
    }
    int query(int L, int R) {
        if(R < lo || hi < L) return inf;
        if(L <= lo && hi <= R) return minVal;
        return min(left->query(L, R), right->query(L, R));
    }
};

void findUseless(vi &useless, vector<pair<tlll, int>> &stations){
    // REVERSE ORDER
    sort(all(stations));
    node segTree(0, mx);
    int start = 0;
    while(start < sz(stations)){
        int end = start + 1;
        while(end < sz(stations) && get<0>(stations[end].first) == get<0>(stations[start].first)){
            end++;
        }
        rep(i, start, end){
            auto &[t, idx] = stations[i];
            auto [t1, t2, t3] = t;
            if(segTree.query(0, t2) <= t3){
                useless[idx] = true;
                // cout << idx << " is useless" << "\n";
            }
        }
        rep(i, start, end){
            auto &[t, idx] = stations[i];
            auto [t1, t2, t3] = t;
            segTree.update(t2, t3);
        }
        start = end;
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, m; cin >> n >> m;
    vvii adj(n);
    rep(i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    auto d0 = dijkstras(adj, 0);
    auto d1 = dijkstras(adj, 1);
    auto d2 = dijkstras(adj, 2);

    vlll list;
    rep(i, 0, n)
        list.emplace_back(d0[i], d1[i], d2[i]);
    cc(list);
    rep(i, 0, n){
        auto [t1, t2, t3] = list[i];
        // cout << i << ": " << t1 << " " << t2 << " " << t3 << "\n";
    }

    vi useless(n);
    {
        // cout << "First pass\n";
        vector<pair<tlll, int>> v;
        int u = 0;
        for(auto [t1, t2, t3] : list){
            v.push_back({{t1, t2, t3}, u});
            u++;
        }
        findUseless(useless, v);
    }
    {
        // cout << "Second pass\n";
        vector<pair<tlll, int>> v;
        int u = 0;
        for(auto [t1, t2, t3] : list){
            v.push_back({{t2, t3, t1}, u});
            u++;
        }
        findUseless(useless, v);
    }
    {
        // cout << "Third pass\n";
        vector<pair<tlll, int>> v;
        int u = 0;
        for(auto [t1, t2, t3] : list){
            v.push_back({{t3, t1, t2}, u});
            u++;
        }
        findUseless(useless, v);
    }
    int cnt = 0;
    rep(i, 0, n){
        if(!useless[i]) cnt++;
    }
    cout << cnt << "\n";

    return 0;
}
