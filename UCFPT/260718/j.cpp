#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using T = pair<ll, int>;
struct node {
    T key;
    node *l = 0, *r = 0;
    int depth = 1;
};
int depth(node *p) {
    if(p) return p->depth;
    return 0;
}
node* merge(node *l, node *r) {
    if(!l || !r) return l ? l : r;
    if(l->key > r->key) swap(l, r);
    node *n = new node(*l);
    n->l = merge(n->l, r);
    if(depth(n->r) < depth(n->l)) swap(n->l, n->r);
    n->depth = 1 + depth(n->l);
    return n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vector<node*> heaps(n);
    ll base = 0;
    vector<vl> grid(n);
    rep(i, 0, n) {
        int m; cin >> m;
        vl a(m);
        rep(j, 0, m) cin >> a[j];
        sort(all(a));
        grid[i] = a;
        base += a[0];
        node *r = NULL;
        rep(j, 1, m) {
            node *p = new node();
            // cerr << "key " << a[j]-a[0] << " at " << i << "," << j << endl;
            p->key = {a[j] - a[0], i};
            r = merge(r, p);
        }
        heaps[i] = r;
    }
    vector<node*> suff(heaps);
    suff.push_back(NULL);
    for(int i = n-1; i >= 0; i--) {
        suff[i] = merge(suff[i], suff[i+1]);
    }
    auto test = [&](ll add) {
        int used = 1;
        ll cost = 0;
        auto dfs = [&](ll cur, int start, auto &&dfs) -> void {
            if(cur > add) return;
            node* adj = suff[start];
            while(adj && used < k && adj->key.first + cur <= add) {
                ll cand = adj->key.first + cur;
                used++;
                cost += cand;
                // cerr << "add lim " << add << " cand " << cand << " used " << used << endl;
                dfs(cand, adj->key.second+1, dfs);
                adj = merge(adj->l, adj->r);
            }
        };
        dfs(0, 0, dfs);
        // cerr << "add " << add << " used " << used << " cost " << cost << endl;
        return pair<int, ll>{used, cost};
    };
    ll add = 0;
    for(ll dif = 1LL << 50; dif; dif /= 2) {
        ll cand = add + dif;
        if(test(cand).first < k) add = cand;
    }
    auto [used, cost] = test(add);
    ll ans = k * base + cost + (add+1) * (k - used);
    cout << ans << "\n";
    // priority_queue<T, vector<T>, greater<>> pq;
    // pq.push({base, -1, -1});
    // ll ans = 0;
    // while(sz(pq)) {
    //     auto [cost, i, j] = pq.top(); pq.pop();
    //     ans += cost;

    // }

    return 0;
}
