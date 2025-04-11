#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
struct PST;
vector<pair<PST*, pii>> st;

const int inf = 2e9;
struct PST {
    PST *l = 0, *r = 0;
    int lo, hi;
    int val = 0; // min in range
    int lz = 0; // max with this
    PST(int lo, int hi) : lo(lo), hi(hi) {
        if(lo+1<hi) {
            int mid = lo + (hi - lo) / 2;
            l = new PST(lo, mid); r = new PST(mid, hi);
        }
    }
    int query(int L, int R) {
        if(R <= lo || hi <= L) return inf;
        if(L <= lo && hi <= R) return val;
        push();
        return min(l->query(L, R), r->query(L, R));
    }
    void chmax(int L, int R, int v) {
        if(R <= lo || hi <= L) return;
        st.push_back({this, {lz, val}});
        if(L <= lo && hi <= R) {
            if(val >= v){
                // do nothing
            } else {
                val = max(val, v);
                lz = max(lz, v);
            }
        }else {
            push();
            l->chmax(L, R, v);
            r->chmax(L, R, v);
            val = min(l->val, r->val);
        }
    }
    void push() {
        if(lz == 0) return;
        st.push_back({this, {lz, val}});
        l->chmax(lo, hi, lz);
        r->chmax(lo, hi, lz);
        lz = 0;
    }
};

struct stst {
    PST* tree;
    vi stsz;
    stst(int s): tree(new PST(0, s)) {
        stsz.push_back(0);
    }

    void push(array<int, 4> q) {
        tree->chmax(q[1], q[2], q[3]);
        stsz.push_back(sz(st));
    }
    void pop() {
        stsz.pop_back();
        int k = stsz.back();
        while(sz(st) > k) {
            auto [point, v] = st.back();
            auto [lz, val] = v;
            point->lz = lz, point->val = val;
            st.pop_back();
        }
    }
};

template<class T, class DS, class Compare =less<T>>
struct PQUpdate {
    DS inner;
    multimap<T, int, Compare> rev_upd;
    using iter = decltype(rev_upd)::iterator;
    vector<iter> st;
    PQUpdate(DS inner, Compare comp={}):inner(inner), rev_upd(comp) {}
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
        for(auto it:extra | views::drop(1) | views::reverse) {
            it->second = sz(st);
            inner.push(it->first);
            st.push_back(it);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<tuple<char, int, int, int>> q;
    vector<int> rem;
    vector<int> coords;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int a, b, h;
            cin >> a >> b >> h;
            coords.push_back(a);
            coords.push_back(b);
            q.push_back({c, a, b, h});
            rem.push_back(n);
        }
        else if (c == '-') {
            int x;
            cin >> x;
            rem[x-1] = i;
            q.push_back({c, x, 0, 0});
        }
        else {
            int l, r;
            cin >> l >> r;
            coords.push_back(l);
            coords.push_back(r);
            q.push_back({c, l, r, 0});
        }
    }

    sort(all(coords));
    coords.erase(unique(all(coords)), coords.end());

    PQUpdate<array<int, 4>, stst, greater<array<int, 4>>> pq(stst(sz(coords)));
    int id = 0;
    for (int i = 0; i < sz(q); i++) {
        auto [c, a, b, h] = q[i];
        while (!pq.empty() && pq.top()[0] < i) pq.pop();
        a = lower_bound(all(coords), a) - coords.begin();
        b = lower_bound(all(coords), b) - coords.begin();
        if (c == '+') {
            pq.push({rem[id++], a, b, h});
        }
        else if (c == '?') {
            cout << pq.inner.tree->query(a, b) << "\n";
        }
    }

    return 0;
}
