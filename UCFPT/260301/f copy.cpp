#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int inf = 1e9;
vi comb(vi l, vi r) {
    vi res;
    int i = 0, j= 0;
    while(i < sz(l) || j < sz(r)) {
        if(j == sz(r) || (i < sz(l) && l[i] > r[j])) {
            if(sz(res) == 0 || res.back() != l[i]) {
                res.push_back(l[i]);
            }
            i++;
        } else {
            if(sz(res) == 0 || res.back() != r[j]) res.push_back(r[j]);
            j++;
        }
    }
    if(sz(res) > 2) res.resize(2);
    return res;
}
struct Node {
    Node *l= 0, *r = 0;
    int lo, hi;
    vi maxes;
    int setmax = -1, lzadd = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            maxes = comb(l->maxes, r->maxes);
        }
        else {
            maxes = vi{inf};
        }
    }
    void add(int L, int R, int x) {
        if(hi <= L || R <= lo) return;
        if(L <= lo && hi <= R) {
            lzadd += x;
            for(auto &i : maxes) i += x;
            if(setmax != -1) setmax += x;
            return;
        }
        push();
        l->add(L, R, x), r->add(L, R, x);
        maxes = comb(l->maxes, r->maxes);
    }
    void chmin(int L, int R, int x) {
        // if(!l) cerr << "at leaf" << endl;
        if(hi <= L || R <= lo) return;
        if(L <= lo && hi <= R) {
            if(maxes[0] <= x) return;
            if(sz(maxes) >= 2 && x <= maxes[1]) {
                push();
                l->chmin(L, R, x), r->chmin(L, R, x);
                maxes = comb(l->maxes, r->maxes);
            } else if(sz(maxes) < 2 || (maxes[1] < x && x < maxes[0])) {
                setmax = x;
                maxes[0] = x;
            }
            return;
        }
        push();
        l->chmin(L, R, x), r->chmin(L, R, x);
        maxes = comb(l->maxes, r->maxes);
    }
    int query(int i) {
        if(lo + 1 == hi) return maxes[0];
        int mid = lo + (hi - lo) / 2;
        push();
        if(mid <= i) return r->query(i);
        else return l->query(i);
    }
    void push() {
        if(!l) return;
        if(lzadd != 0) {
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd);
            lzadd = 0;
        }
        if(setmax != -1) {
            l->chmin(lo, hi, setmax), r->chmin(lo, hi, setmax);
            setmax = -1;
        }
    }
    int getmin(int L, int R) {
        if(hi <= L || R <= lo) return inf;
        if(lo+1 == hi) {
            return maxes[0];
        }
        push();
        return min(l->getmin(L, R), r->getmin(L, R));
    }
    void dfs() {
        if(lo+1==hi) {
            cerr << lo << ": " << maxes[0] << endl;
            return;
        }
        push();
        l->dfs(), r->dfs();
    }
};
using int128 = __int128_t;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int l, r, n; cin >> l >> r >> n;
    vector<array<int, 4>> rng(n);
    vi c;
    c.push_back(l);
    c.push_back(r);
    rep(i, 0, n) {
        rep(j, 0, 4) {
            cin >> rng[i][j];
            if(j % 2 == 0) {
                c.push_back(rng[i][j]);
            }
        }
    }
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    auto get_idx = [&](int x) {
        return lower_bound(all(c), x) - begin(c);
    };
    l = get_idx(l);
    r = get_idx(r);
    rep(i, 0, n) {
        // cerr << i << ": ";
        rep(j, 0, 4) {
            if(j % 2 == 0) rng[i][j] = get_idx(rng[i][j]);
            // cerr << rng[i][j] << " ";
        }
        // cerr << endl;
    }
    int128 eval_point = 0;
    auto cmp = [&](int i, int j) -> bool {
        int128 dyi = (rng[i][3] - rng[i][1]);
        int128 dyj = (rng[j][3] - rng[j][1]);
        int128 dxi = (c[rng[i][2]] - c[rng[i][0]]);
        int128 dxj = (c[rng[j][2]] - c[rng[j][0]]);
        assert(dxi != 0 && dxj != 0);
        // auto res = ld(dyi) / dxi * (eval_point - rng[i][0]) + rng[i][1] > ld(dyj) / dxj * (eval_point - rng[j][0]) + rng[j][1];

        int128 term = dxi * dxj;
        bool flip = term < 0;
        auto left = dyi * dxj * (eval_point - c[rng[i][0]]) + rng[i][1]*dxi*dxj;
        auto right = dyj * dxi * (eval_point - c[rng[j][0]]) + rng[j][1]*dxi*dxj;
        if(flip) return left < right;
        return left > right;
        // if(res != res1) {
        //     cerr << i << " " << j << " " << res << " " << res1 << endl;
        //     exit(0);
        // }
        // return res;
        // ll left = dyi * dxj * (eval_point - rng[i][0]) + rng[i][1] * dxi * dxj;
        // ll right = dyj * dxi * (eval_point - rng[j][0]) + rng[j][1] * dxi * dxj;
        // bool res = left > right;
        // cerr << "cmp " << i << " < " << j << " = " << res << " eval at " << eval_point << " left " << left << " right " << right << endl;
        // return res;
    };
    set<int, decltype(cmp)> lines(cmp);
    vvi adj(n);
    auto dnc = [&](vi idxs, int l, int r, auto &&dnc) -> void {
        vi full, left, right;
        int mid = l + (r-l) / 2;
        for(int i : idxs) {
            auto [minx, maxx_tmp] = minmax(rng[i][0], rng[i][2]);
            auto maxx = maxx_tmp+1;
            if(maxx <= l || r <= minx) continue;
            if(minx <= l && r <= maxx) {
                full.push_back(i);
            }
            else if(l+1 < r) {
                left.push_back(i), right.push_back(i);
            }
        }
        // cerr << "l " << l << " r " << r << " full ";
        // for(int i : full) cerr << i << ",";
        // cerr << endl;
        idxs = vi();
        eval_point = c[l];
        for(int i : full) {
            auto it = lines.lower_bound(i);
            if(it != end(lines)) {
                adj[i].push_back(*it);
            }
            if(it != begin(lines)) {
                it--;
                adj[*it].push_back(i);
            }
            lines.insert(i);
        }
        // cerr << "set: ";
        // for(int i : lines) cerr << i << " ";
        // cerr << endl;
        if(l+1 < r) {
            dnc(left, l, mid, dnc);
            dnc(right, mid, r, dnc);
        }
        eval_point = c[l];
        for(int i : full) {
            lines.erase(i);
        }
    };
    vi idxs(n);
    iota(all(idxs), 0);
    dnc(idxs, 0, sz(c), dnc);
    // rep(i, 0, n) {
    //     cerr << i << ": ";
    //     for(int j : adj[i]) cerr << j << ",";
    //     cerr << endl;
    // }
    vi ts, color(n);
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(color[u]) {
            if(color[u] == 1) {
                while(true);
                cout << -1 << "\n";
                exit(0);
            }
            assert(color[u] == 2);
            return;
        }
        color[u] = 1;
        for(int v : adj[u]) dfs(v, dfs);
        color[u] = 2;
        ts.push_back(u);
    };
    rep(i, 0, n) dfs(i, dfs);
    Node tree(0, sz(c));
    tree.chmin(l, r+1, 0);
    // cerr << "ts: ";
    // for(int i : ts) cerr << i << ",";
    // cerr << endl;
    for(int i : ts) {
        int dp = tree.query(rng[i][0]);
        int le = rng[i][0], ri = rng[i][2];
        if(le > ri) swap(le, ri);
        tree.add(le+1, ri, 1);
        tree.chmin(le, ri+1, dp);
        // cerr << i << " dp " << dp << ": ";
        // tree.dfs();
        // cerr << endl;
    }
    cout << tree.getmin(l, r+1) << "\n";


    return 0;
}
