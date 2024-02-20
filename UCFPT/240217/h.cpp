#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define rep(i, a, b) for(int i = a; i < b; i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
#define pb push_back
vi val, comp, z, cont;
int Time, ncomps;
template < class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.pb(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));
    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.pb(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}

template < class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}

/*
bad conditions:
2sat doesn't work
an A reaches another A
an E before an A in the same SCC
an A is fixed
an E fixed to true reaches an A
an E fixed to true reaches an E fixed to false
an A reaches an E fixed to false

other considerations:
an E which reaches an A is false
an E which is reached by an A is true


A reaches A - straight up bad
E reaches A and is before   E must be false or is bad, so as good as fixing to false
E reaches A and is after    is bad if E is fixed to true, may as well fix to false?
E reaches E                 only bad if first is fixed to true and second is fixed to false
A reaches E and is before   is bad if E fixed to false, may as well fix E to true?
A reaches E and is after    is bad if E fixed to false, as good as fixing E to true
E samescc E                 set both to be equal

facts derived from above:
one A on any path
an E is reached by A, reaches A, or has no A
should fix E reached by A to true
should fix E reaching A to false




*/

// some bitset bs goin on here
const int BITS = 32;
struct bs {
    vi s;
    bs(int bits) {
        s.resize((bits + BITS - 1) / BITS);
    }
    void set(int b) {
        s[b / BITS] |= 1 << (b % BITS);
    }
    int get(int b) {
        return s[b / BITS] >> (b % BITS);
    }
    bs& operator |=(bs &o){
        rep(i, 0, sz(s)){
            s[i] |= o.s[i];
        }
        return *this;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vvi g(n * 2);
    string quant; cin >> quant;
    auto invert = [&](int u) -> int {
        if(u >= n) return u - n;
        return u + n;
    };
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a = (a > 0 ? a-1 : -(a+1) + n);
        b = (b > 0 ? b-1 : -(b+1) + n);
        g[invert(a)].pb(b);
        g[invert(b)].pb(a);
    }
    vi belong(2 * n, -1);
    vvi sccs;
    vi lasta, firste, numa;
    bool works = true;
    auto getscc = [&](vi comp) -> void {
        sccs.pb(comp);
        lasta.pb(-1);
        firste.pb(3 * n);
        numa.pb(0);
        for(int u : comp){
            if(quant[(u % n)] == 'A'){
                lasta[ncomps] = max(lasta[ncomps], u % n);
                numa[ncomps]++;
            }
            else{
                firste[ncomps] = min(firste[ncomps], u % n);
            }
        }
        if(firste[ncomps] <= lasta[ncomps]) works = false; // no E before A in same SCC
        if(numa[ncomps] > 1) works = false; // not multiple A in one SCC
    };
    scc(g, getscc);
    vvi adj(ncomps), radj(ncomps);
    vi reachesa = numa, areaches = numa;
    for(int i = 0; i < 2 * n; i++){
        if(i < n && comp[i] == comp[i + n]) works = false; // check 2sat possible
        for(int j : g[i]){
            if(comp[i] != comp[j]){
                adj[comp[i]].pb(comp[j]);
                radj[comp[j]].pb(comp[i]);
            }
        }
    }
    vi calcd(ncomps);
    vector<bs> reaches(ncomps, bs(ncomps));
    auto go = [&](int u, auto &&go) -> void {
        if(calcd[u]) return;
        calcd[u] = true;
        reaches[u].set(u);
        for(int v : adj[u]){
            go(v, go);
            // firste[u] = min(firste[u], firste[v]);
            reaches[u] |= reaches[v];
            if(reachesa[u] && reachesa[v]){
                // can't have an A before an A
                works = false;
            }
            reachesa[u] += reachesa[v];
        }
    };
    vi fixed(n); // 1 true 2 false
    rep(i, 0, ncomps){
        go(i, go);
    }
    calcd = vi(ncomps);
    auto findbad = [&](int u, auto &&findbad) -> void {
        if(calcd[u]) return;
        calcd[u] = true;
        for(int v : radj[u]){
            findbad(v, findbad);
            areaches[u] += areaches[v];
        }
    };
    rep(i, 0, ncomps){
        findbad(i, findbad);
    }
    rep(i, 0, n){
        if(reaches[comp[i]].get(comp[invert(i)])){
            fixed[i] |= 2;
        }
        if(reaches[comp[invert(i)]].get(comp[i])){
            fixed[i] |= 1;
        }
        if(quant[i] == 'E'){
            if(reachesa[comp[i]] - numa[comp[i]]) fixed[i] |= 2;
            if(reachesa[comp[invert(i)]] - numa[comp[invert(i)]]) fixed[i] |= 1;
            if(areaches[comp[i]] - numa[comp[i]]) fixed[i] |= 1;
            if(areaches[comp[invert(i)]] - numa[comp[invert(i)]]) fixed[i] |= 2;
        }
        if(fixed[i] == 3){
            works = false;
        }
    }
    cout << (works ? "TRUE" : "FALSE") << "\n";

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }

    return 0;
}