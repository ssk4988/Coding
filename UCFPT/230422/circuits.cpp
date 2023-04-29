#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using ll = long long;
using vpi = vector<pair<int, int>>;
using vl = vector<ll>;
using ld = long double;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
#define nL "\n"



int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; 
    while(true){
        cin >> n;
        if(n == 0) break;
        vector<unordered_map<int, ld>> adj(26);
        auto merge = [&](int a, int b, ld c)->void{
            // if(a == b) return;
            if(a > b) swap(a, b);
            if(adj[a][b] == 0){
                adj[a][b] = c;
            }
            else{
                adj[a][b] = 1/(1 / adj[a][b] + 1/c);
            }
            adj[b][a] = adj[a][b];
        };
        auto combine = [&](int a, int b, int c){
            assert(sz(adj[b]) == 2);
            assert(a != c);
            ld neww = adj[a][b] + adj[b][c];
            adj[a].erase(b);
            adj[b].erase(a);
            adj[b].erase(c);
            adj[c].erase(b);
            merge(a, c, neww);
        };
        // how to deal with self-loop/cycles?
        bool bad = false;
        rep(i, 0, n){
            string a, b; cin >> a >> b;
            int w; cin >> w;
            int a1 = a[0] - 'A', b1 = b[0] - 'A';
            merge(a1, b1, w);
            if(a1 == b1) bad = true;
        }
        if(bad){
            cout << "-1.000\n";
            continue;
        }
        // auto dfs = [&](int cur, vi &st, vi &visited, auto &&dfs)->void{
        //     if(visited[cur]) return;
        //     visited[cur] = true;
        //     st.pb(cur);
        //     for(auto &p : adj[cur]){
        //         auto [nex, w] = p;
                
        //     }
        // };
        queue<int> q;
        rep(i, 0, 26){
            if(sz(adj[i]) == 2 && i != 0 & i != 25){
                q.push(i);
            }
        }
        while(!q.empty()){
            int k = q.front();q.pop();
            if(sz(adj[k]) != 2 || k == 0 || k == 25){
                continue;
            }
            vi adj2;
            for(auto &p : adj[k]){
                adj2.pb(p.f);
            }
            combine(adj2[0], k, adj2[1]);
            for(int i : adj2){
                    if(sz(adj[i]) == 2 && i != 0 & i != 25){
                    q.push(i);
                }
            }
        }
        bad = false;
        rep(i, 0, 26){
            if((i == 0 || i == 25) && sz(adj[i]) != 1) bad = true;
            if(i != 0 && i != 25 && sz(adj[i]) != 0) bad = true;
        }
        if(bad){
            cout << "-1.000\n";
            continue;
        }
        else{
            cout << fixed << setprecision(3) << adj[0][25] << nL;
        }

        // MAKE SURE TO ROUND AND DISPLAY
        // cout << fixed << setprecision(3) << 0.0149 << nL;
        // seems good
    }




    return 0;
}