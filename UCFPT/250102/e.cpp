#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)


const int N = 300;
using bs = bitset<N>;
int n, k;
bool operator<(const bs &a, const bs &b) {
    // return a.to_string() < b.to_string();
    rep(i, 0, n){
        if(a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}
struct basis {
    vector<bs> b;
    vi v;
    vi idx;
    void shrink(bs &x, int &val) {
        rep(i, 0, sz(b)){
        // for(auto &y : b){
            auto &y = b[i];
            if(x[idx[i]]) x ^= y, val ^= v[i];
        }
    }
    bool add(bs x, int y) {
        // if(sz(b) == n) return false;
        shrink(x, y);
        if(x.count()) {
            idx.push_back(-1);
            rep(i, 0, n){
                if(x[i]) {idx.back() = i; break;}
            }
            rep(i, 0, sz(b)){
                auto &o = b[i];
                if(o[idx.back()]) o ^= x, v[i] ^= y;
            }
            b.push_back(x);
            v.push_back(y);
            return true;
        }
        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n-1) {
        int x, y; cin >> x >> y; x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    auto dfs = [&](int u, int p, int t, vi &path, auto &&dfs) -> bool {
        path.push_back(u);
        if(u == t){
            return true;
        }
        for(int v : adj[u]) if(v != p) {
            if(dfs(v, u, t, path, dfs)) return true;
        }
        path.pop_back();
        return false;
    };
    basis b;
    vvi use;
    {
        bs d;
        d[0] = 1;
        b.add(d, 0);
    }
    rep(i, 0, n){
        rep(j, i+1, n){
            vi path;
            dfs(i, -1, j, path, dfs);
            if(sz(path) == k+1) {
                bs v;
                for(int u : path) v[u] = 1;
                if(b.add(v, 0)) use.push_back(path);
            }
        }
    }
    if(sz(b.b) != n){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    cout << "? " << sz(use) << " ";
    for(auto &v : use){
        cout << v[0]+1 << " " << v.back()+1 << " ";
    }
    cout << endl;
    b = basis();
    {
        bs d;
        d[0] = 1;
        b.add(d, 0);
    }
    for(auto &v : use) {
        int res; cin >> res;
        bs x;
        for(auto u : v) x[u] = 1;
        assert(b.add(x, res));
    }
    vi res(n);
    rep(i, 0, sz(b.v)) {
        rep(j, 0, n){
            if(b.b[i][j]){
                res[j] = b.v[i];
            }
        }
    }
    cout << "! ";
    rep(i, 1, n) cout << res[i] << " ";
    cout << "\n";
 
    return 0;
}
