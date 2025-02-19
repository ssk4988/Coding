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

template<class T, class DS, class Compare = less<T>>
struct PQUpdate {
    DS inner;
    multimap<T, int, Compare> rev_upd;
    using iter = typename decltype(rev_upd)::iterator;
    vector<iter> st;
    PQUpdate(DS inner, Compare comp={}):
        inner(inner), rev_upd(comp) {}
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
        for(int i = sz(extra)-1; i > 0; i--) {
            auto it = extra[i];
            it->second = sz(st);
            inner.push(it->first);
            st.push_back(it);
        }
    }
};
using DSUUpdate = array<int, 3>;
struct DSU {
    vi e;
    vector<array<int, 5>> st;
    DSU(int n): e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    bool sameSet(int x, int y) { return find(x) == find(y); }
    bool join(int x, int y) {
        // cerr << "join " << x << "," << y << endl;
        x = find(x), y = find(y);
        if(x == y) {
            st.push_back({0, -1, -1, -1, -1});
            return false;
        }
        if(e[x] > e[y]) swap(x, y);
        // cerr << "stack update" << endl;
        st.push_back({1, x, e[x], y, e[y]});
        e[x] += e[y]; e[y] = x;
        return true;
    }
    void push(DSUUpdate u) {
        auto [t, x, y] = u;
        join(x, y);
    }
    void pop() {
        assert(sz(st));
        auto [t, x, ex, y, ey] = st.back();
        st.pop_back();
        if(t) {
            // cerr << "do pop, undo to " << x << " " << ex << " " << y << " " << ey << endl;
            e[x] = ex;
            e[y] = ey;
        }
    }
};


const int inf = 1e9;
int solve_horiz(vector<string> grid) {
    int n = sz(grid), m = sz(grid[0]);
    // cerr << "current grid: " << endl;
    rep(i, 0, n) {
        // cerr << grid[i] << endl;
    }
    auto to_id = [&](int r, int c) { return r * m + c; };
    pii f, s;
    int sid=-1, fid=-1;
    PQUpdate<DSUUpdate, DSU, greater<DSUUpdate>> pq(DSU(n*m), greater<DSUUpdate>());
    DSU& dsu = pq.inner;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if(grid[i][j] == 's') {
                s = {i, j};
                sid = to_id(i, j);
            }
            else if(grid[i][j] == 'f') {
                f = {i, j};
                fid = to_id(i, j);
            }
        }
    }
    auto issf = [&](int r, int c) { return grid[r][c] == 's' || grid[r][c] == 'f'; };
    auto isunblocked = [&](int r, int c) { return grid[r][c] != '#'; };
    rep(i, 0, n) {
        rep(j, 0, m) {
            if(i+1 < n && grid[i][j] == '.' && isunblocked(i+1, j)) {
                pq.push({to_id(i, j), to_id(i, j), to_id(i+1, j)});
                // cerr << "init " << i << " " << j << " to " << i+1 << " " << j << endl;
            }
            if(j+1 < m && grid[i][j] == '.' && isunblocked(i, j+1)) {
                pq.push({to_id(i, j), to_id(i, j), to_id(i, j+1)});
                // cerr << "init " << i << " " << j << " to " << i << " " << j+1 << endl;
            }
            if(i && grid[i][j] == '.' && issf(i-1, j)) {
                pq.push({to_id(i, j), to_id(i, j), to_id(i-1, j)});
            }
            if(j && grid[i][j] == '.' && issf(i, j-1)) {
                pq.push({to_id(i, j), to_id(i, j), to_id(i, j-1)});
            }
            if(i+1 < n && issf(i, j) && issf(i+1, j)){
                pq.push({inf, to_id(i, j), to_id(i+1, j)});
            }
            if(j+1 < m && issf(i, j) && issf(i, j+1)) {
                pq.push({inf, to_id(i, j), to_id(i, j+1)});
            }
        }
    }
    // cerr << "currently connected: " << dsu.sameSet(fid, sid) << endl;
    // cerr << "fid: " << f.first << " " << f.second << endl;
    // cerr << "sid: " << s.first << " " << s.second << endl;
    int ans = inf;
    rep(r, 0, n) {
        int c2 = 0;
        rep(c1, 0, m) {
            if(grid[r][c1] != '.') continue;
            c2 = max(c1, c2);
            while(c2 < m && dsu.sameSet(sid, fid) && grid[r][c2] == '.') {
                while(!pq.empty() && pq.top()[0] == to_id(r, c2)) {
                    auto [t, x, y] = pq.top();
                    // cerr << "Popping " << t << " " << x << " " << y << endl;
                    pq.pop();
                }
                c2++;
            }
            if(!dsu.sameSet(sid, fid)) {
                // cerr << r << " " << c1 << " " << c2 << " works" << endl;
                ans = min(ans, c2-c1);
            }
            // add c1 edges
            if(r && grid[r-1][c1] != '#') {
                pq.push({inf, to_id(r, c1), to_id(r-1, c1)});
            }
            if(r+1 < n && grid[r+1][c1] != '#') {
                int prior = grid[r+1][c1] == '.' ? to_id(r+1, c1) : inf;
                pq.push({prior, to_id(r, c1), to_id(r+1, c1)});
            }
            if(c1 && grid[r][c1-1] != '#') {
                pq.push({inf, to_id(r, c1), to_id(r, c1-1)});
            }
            if(c1+1<m && grid[r][c1+1] != '#') {
                if(grid[r][c1+1] != '.') {
                    pq.push({inf, to_id(r, c1), to_id(r, c1+1)});
                } else if(c1+1 >= c2) {
                    pq.push({to_id(r, c1+1), to_id(r, c1), to_id(r, c1+1)});
                } 
            }
        }
    }
    return ans;
}
void solve() {
    int n, m; cin >> n >> m;
    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }
    int ans1 = solve_horiz(grid);
    vector<string> grid2(m);
    rep(i, 0, n) {
        rep(j, 0, m) {
            grid2[j].push_back(grid[i][j]);
        }
    }
    int ans2 = solve_horiz(grid2);
    int ans = min(ans1, ans2);
    if(ans == inf) cout << "-1\n";
    else cout << ans << "\n";
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    return 0;
}
