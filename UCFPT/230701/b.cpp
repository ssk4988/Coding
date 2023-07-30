#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

struct UF{
    vi e;
    vl lz;
    vector<vector<pair<int, ll>>> child;
    UF(int n) : e(n, -1), child(n), lz(n) {
        rep(i, 0, n) child[i].pb({i, 0});
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) {return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b, ll c){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        int sza = size(a), szb = size(b);
        lz[a] += szb * c, lz[b] += sza * c;
        for(auto [i, v] : child[b]){
            child[a].pb({i, v + lz[b] - lz[a]});
        }
        child[b].clear();
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main() {
    freopen("road.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        UF uf(n);
        vector<pair<ll, pi>> es;
        rep(i, 0, m){
            int x, y, c; cin >> x >> y >> c;
            x--,y--;
            es.pb({c, {x, y}});
        }
        sort(all(es));
        rep(i, 0, m){
            uf.join(es[i].s.f, es[i].s.s, es[i].f);
        }
        vl ans(n);
        int par = uf.find(0);
        for(auto [i, v] : uf.child[par]){
            ans[i] = v + uf.lz[par];
        }
        cout << "Case " << (cn + 1) << ":\n";
        rep(i, 0, n){
            cout << ans[i] << "\n";
        }
    }
}
