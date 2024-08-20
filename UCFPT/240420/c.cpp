#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for(auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));

    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while(x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if( comp[i] < 0) dfs(i, g, f);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vi votes(m);
    vvi pref(m, vi(n));
    rep(i, 0, m){
        cin >> votes[i];
        string str; cin >> str;
        rep(j, 0, n){
            pref[i][str[j] - 'A'] = j;
        }
    }
    vvi adj(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == j) continue;
            int sc = 0;
            rep(k, 0, m){
                if(pref[k][i] < pref[k][j]) sc += votes[k];
                else sc -= votes[k];
            }
            if(sc > 0) {
                adj[i].push_back(j); 
                // cout << i << " to " << j << "\n";
            }
        }
    }
    vvi sccs;
    auto add = [&](vi v)->void {
        sccs.push_back(v);
    };
    scc(adj, add);
    int s = sz(sccs);
    rep(i, 0, n){
        cout << char('A' + i) << ": " << (comp[i] == s - 1 ? "can win" : "can't win") << "\n";
    }
    

    return 0;
}