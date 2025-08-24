#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

const int inf = 1e9;

struct info {
    int ux = inf, uy = inf, vx = inf, vy = inf;
    int res = inf;
    info() {}
    info(int s, int x, int y) {
        if(s == 1) ux = x, uy = y;
        else vx = x, vy = y;
    }
    info operator+(info o) {
        info out;
        out.ux = min(ux, o.ux);
        out.uy = min(uy, o.uy);
        out.vx = min(vx, o.vx);
        out.vy = min(vy, o.vy);
        out.res = min({res, o.res, o.ux + vx, o.vy + uy});
        return out;
    }
};

int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2/2);
}

using upd = tuple<int, int, info>;

bool operator<(upd u, upd v) {
    return get<0>(u) < get<0>(v);
}

bool operator>(upd u, upd v) {
    return get<0>(u) > get<0>(v);
}

struct seg_tree {
    vector<info> tree;
    vector<pair<int, info>> stk;
    seg_tree(int n): tree(2*n) {}
    int query() {
        int res = tree[1].res;
        return res == inf ? -1 : res;
    }
    void update(int i, info v, int tl, int tr, int ti) {
        if(tr - tl == 1) {
            stk.emplace_back(ti, tree[ti]);    
            tree[ti].ux = min(v.ux, tree[ti].ux);
            tree[ti].uy = min(v.uy, tree[ti].uy);
            tree[ti].vx = min(v.vx, tree[ti].vx);
            tree[ti].vy = min(v.vy, tree[ti].vy);
            tree[ti].res = min(tree[ti].ux + tree[ti].vx, tree[ti].uy + tree[ti].vy);
            return;
        }
        int tm = split(tl, tr);
        if(i < tm) update(i, v, tl, tm, 2*ti);
        else update(i, v, tm, tr, 2*ti+1);
        stk.emplace_back(ti, tree[ti]);
        tree[ti] = tree[2*ti] + tree[2*ti+1];
    }
    void push(upd u) {
        auto [_, i, v] = u;
        stk.emplace_back(-1, info());
        update(i, v, 0, sz(tree)/2, 1);
    }
    void pop() {
        while(true) {
            auto [i, v] = stk.back();
            stk.pop_back();
            if(i == -1) break;
            tree[i] = v;
        }
    }
};

template<class T, class DS, class Compare = less<T>>
struct PQUpdate {
    DS inner;
    multimap<T, int, Compare> rev_upd;
    using iter = decltype(rev_upd)::iterator;
    vector<iter> st;
    PQUpdate(DS inner, Compare comp={}): inner(inner), rev_upd(comp) {}
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
        } while (2*sz(extra) < sz(st) - min_ind);
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

const int off = 250000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q; cin >> q;
    vector<array<int, 4>> ranges(q+1, {-1, -1, -1, -1});
    map<array<int, 3>, vi> pts;

    rep(i, 0, q) {
        int t, s, x, y; 
        cin >> t >> s >> x >> y;
        if(t == 1) {
            pts[{s, x, y}].push_back(i);
        }
        else {
            int l = pts[{s, x, y}].back();
            pts[{s, x, y}].pop_back();
            ranges[l] = {i, s, x, y};
        }
    }

    for(auto [p, v]: pts) {
        for(int i: v)
            ranges[i] = {inf, p[0], p[1], p[2]};
    }

    PQUpdate<upd, seg_tree, greater<upd>> pq(seg_tree(2*off+1), greater<upd>());

    rep(L, 0, q) {
        while(!pq.empty() && get<0>(pq.top()) <= L) pq.pop();
        auto [R, s, x, y] = ranges[L];
        if(R != -1) {
            if(s == 1)
                pq.push(upd(R, x-y+off, info(s, x, y)));
            else
                pq.push(upd(R, y-x+off, info(s, x, y)));
        }
        cout << pq.inner.query() << '\n';
    }

    return 0;
}
