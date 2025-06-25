#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

const int V = 10;
struct UF {
    vvi e;
    vector<vector<array<int, 3>>> st;
    UF(int n) : e(V, vi(n, -1)), st(V) {}
    int find(int w, int x) { return e[w][x] < 0 ? x : find(w, e[w][x]); }
    void join(int u, int v, int w) {
        rep(t, w, V) {
            int a = find(t, u), b = find(t, v);
            if(a == b) {
                st[t].push_back(array<int, 3>{-1, -1, -1});
                continue;
            }
            if(e[t][a] > e[t][b]) swap(a, b);
            st[t].push_back({a, b, e[t][b]});
            e[t][a] += e[t][b]; e[t][b] = a;
        }
        rep(t, 0, w) st[t].push_back(array<int, 3>{-1, -1, -1});
        // rep(t, 0, V) assert(sz(st[t]) == sz(st[0]));
    }
    void push(array<int, 4> u) {
        // cerr << "push: ";
        // rep(i, 0, 4) cerr << u[i] << " ";
        // cerr << endl;
        join(u[1], u[2], u[3]);
    }
    void pop() {
        // cerr << "pop" << endl;
        rep(t, 0, V) {
            auto [a, b, eb] = st[t].back(); st[t].pop_back();
            if(a == -1) continue;
            e[t][a] -= eb;
            e[t][b] = eb;
        }
    }
};

template<class T, class DS, class Compare = less<T>>
struct PQUpdate {
    DS inner;
    multimap<T, int, Compare> rev_upd;
    using iter = decltype(rev_upd)::iterator;
    vector<iter> st;
    PQUpdate(DS inner, Compare comp = {}): inner(inner), rev_upd(comp) {}
    bool empty() { return st.empty(); }
    const T& top() { return rev_upd.rbegin()->first; }
    void push(T value) {
        inner.push(value);
        st.push_back(rev_upd.insert({value, sz(st)}));
    }
    void pop() {
        vector<iter> extra;
        iter curr = rev_upd.end();
        int min_ind = sz(st);
        do {
            extra.push_back(--curr);
            min_ind = min(min_ind, curr->second);
        } while(2 * sz(extra) < sz(st) - min_ind);
        while(sz(st) > min_ind) {
            if(rev_upd.value_comp()(*st.back(), *curr))
                extra.push_back(st.back());
            inner.pop(); st.pop_back();
        }
        rev_upd.erase(extra[0]);
        for(auto it : extra | views::drop(1) | views::reverse) {
            it->second = sz(st);
            inner.push(it->first);
            st.push_back(it);
        }
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    PQUpdate<array<int, 4>, UF, greater<array<int, 4>>> pq{UF(n)};
    UF& uf = pq.inner;
    vector<vector<array<int, 4>>> upd(q); // u, v, w, expires
    vii query(q, pii{-1, -1});
    map<pii, pii> edges; // for given u,v, creation time and value
    rep(t, 0, q) {
        int tp, u, v; cin >> tp >> u >> v; if(u > v) swap(u, v);
        if(tp == 0) {
            int w; cin >> w;
            edges[{u, v}] = {t, w};
        } else if(tp == 1) {
            auto [t1, w] = edges[{u, v}];
            upd[t1].push_back({u, v, w, t});
            edges.erase({u, v});
        } else {
            query[t] = {u, v};
        }
    }
    for(auto [key, val] : edges) {
        auto [u, v] = key;
        auto [t, w] = val;
        upd[t].push_back({u, v, w, q});
    }
    rep(t, 0, q) {
        for(auto [u, v, w, expires] : upd[t]) {
            // cerr << "upd " << u << " " << v << " " << w << " " << expires << endl;
            pq.push({expires, u, v, w});
        }
        while(!pq.empty() && pq.top()[0] <= t) {
            pq.pop();
        }
        if(query[t].first != -1) {
            auto [u, v] = query[t];
            int ans = -1;
            // cerr << "answering " << t << " " << u << " " << v << endl;
            rep(i, 0, V) {
                if(uf.find(i, u) == uf.find(i, v)) {
                    ans = i;
                    break;
                }
            }
            cout << ans << "\n";
        }
    }



    return 0;
}
