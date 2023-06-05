#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f){
    int low = val[j] = ++Time, x; z.pb(j);
    for(auto e: g[j]) if(comp[e] < 0)
        low = min(low, val[e] ?: dfs(e, g, f));
    
    if(low == val[j]){
        do{
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.pb(x);
        } while(x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
void doNothing(vi v){

}
template<class G, class F> void scc(G& g, F f){
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if(comp[i] < 0) dfs(i, g, f);
}



int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    auto label = [&](int var, bool itself)->int{
        return 2 * var + itself;
    };
    auto unlabel = [&](int v)->pi{
        return {v / 2, v % 2};
    };
    vvi adj(2 * n);
    auto setTrue = [&](int var)->void{
        adj[label(var, false)].pb(label(var, true));
    };
    auto setFalse = [&](int var)->void{
        adj[label(var, true)].pb(label(var, false));
    };
    auto implies = [&](int v1, int v2)->void{
        adj[v1].pb(v2);
        adj[v2^1].pb(v1^1);
    };
    auto equals = [&](int v1, int v2)->void{
        implies(v1, v2);
        implies(v2, v1);
    };
    auto notequals = [&](int v1, int v2)->void{equals(v1, v2^1);};
    auto ored = [&](int var1, int var2)->void{
        implies(label(var1, false), label(var2, true));
        implies(label(var2, false), label(var1, true));
    };
    rep(i, 0, m){
        int a, b, c; string op; cin >> a >> b >> op >> c;
        if(op[0] == '='){
            if(c == 0){
                setFalse(a);setFalse(b);
            }
            if(c == 1){
                notequals(label(a, true), label(b, true));
            }
            if(c == 2){
                setTrue(a); setTrue(b);
            }
        }
        else if(op[0] == '!'){
            if(c == 0){
                ored(a, b);
            }
            if(c == 1){
                equals(label(a, true), label(b, true));
            }
            if(c == 2){
                implies(label(a, true), label(b, false));
                implies(label(b, true), label(a, false));
            }
        }
        else if(op[0] == '<' && sz(op) == 1){
            if(c == 0){
                cout << "No\n";
                return 0;
            }
            if(c == 1){
                setFalse(a);setFalse(b); // = 0
            }
            if(c == 2){
                implies(label(a, true), label(b, false));
                implies(label(b, true), label(a, false));
                // != 2
            }
        }
        else if(op[0] == '>' && sz(op) == 1){
            if(c == 0){
                ored(a, b); // != 0
            }
            if(c == 1){
                setTrue(a); setTrue(b); // = 2
            }
            if(c == 2){
                cout << "No\n";
                return 0;
            }
        }
        else if(op[0] == '<' && sz(op) == 2){
            if(c == 0){
                setFalse(a);setFalse(b); // = 0
            }
            if(c == 1){
                implies(label(a, true), label(b, false));
                implies(label(b, true), label(a, false));
                // != 2
            }
            if(c == 2){
                // bruh
            }
        }
        else if(op[0] == '>' && sz(op) == 2){
            if(c == 0){
                // bruh
            }
            if(c == 1){
                ored(a, b); // != 0
            }
            if(c == 2){
                setTrue(a); setTrue(b); // = 2
            }
        }
        else{
            assert(false);
        }
    }
    scc(adj, doNothing);
    bool bad = false;
    rep(i, 0, n){
        if(comp[label(i, true)] == comp[label(i, false)]){
            bad = true;
        }
    }
    cout << (bad ? "No" : "Yes") << "\n";

    return 0;
}
