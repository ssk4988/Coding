#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn,0, nc){
        int n; cin >> n;
        vector<set<int>> adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        set<int> leaves;
        rep(i,0,n){
            if(sz(adj[i]) == 1) leaves.insert(i);
        }
        int ans = 0;
        int firsttime = true;
        while(sz(leaves)){
            int bruh = *leaves.begin();
            int root = -1;
            if(firsttime) {
                for(int leaf : leaves){
                    for(int v : adj[leaf]){
                        if(sz(adj[v]) == 2) {
                            root = leaf;
                        }
                    }
                }
                if(root == -1) root = bruh;
            }
            else root = *adj[bruh].begin();
            for(int v : adj[root]){
                adj[v].erase(root);
                if(sz(adj[v]) == 0){
                    // cut leaf
                    ans++;
                    leaves.erase(v);
                }
                else if(sz(adj[v]) == 1) leaves.insert(v); // made leaf
            }
            adj[root].clear();
            if(leaves.count(root)) {
                leaves.erase(root);
                if(firsttime) ans++;
            }
            firsttime = false;
        }
        rep(i, 0, n) assert(sz(adj[i]) == 0);
        cout << ans << "\n";
    }
    
    return 0;
}
