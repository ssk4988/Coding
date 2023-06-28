#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    while(true){
        cin >> n;
        if(n == 0) break;
        vvi adj(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b;
            a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi height(n);
        vector<unordered_map<int, int>> dep(n);
        auto dfs = [&](int cur, int par, auto &&dfs)->void{
            height[cur] = 0;
            vpi hs;
            for(int i : adj[cur]){
                if(i == par) continue;
                dfs(i, cur, dfs);
                height[cur] = max(height[cur], 1 + height[i]);
                hs.pb({1 + height[i], i});
            }
            dep[cur][par] = height[cur];
            if(par != -1){
                hs.pb({dep[par][cur], par});
            }
            sort(all(hs));
            reverse(all(hs));
            for(int i : adj[cur]){
                if(i == par) continue;
                if(sz(hs) && i != hs[0].s){
                    dep[cur][i] = hs[0].f;
                }
                else if(sz(hs) > 1){
                    dep[cur][i] = hs[1].f;
                }
                else{
                    dep[cur][i] = 0;
                }
            }
        };
        dfs(n - 1, -1, dfs);
        auto dfs2 = [&](int cur, int par, auto &&dfs2)->void{
            vpi hs;
            for(int i : adj[cur]){
                if(i == par) continue;
                hs.pb({1 + height[i], i});
            }
            dep[cur][par] = height[cur];
            if(par != -1){
                hs.pb({1 + dep[par][cur], par});
            }
            sort(all(hs));
            reverse(all(hs));
            for(int i : adj[cur]){
                if(i == par) continue;
                if(sz(hs) && i != hs[0].s){
                    dep[cur][i] = hs[0].f;
                }
                else if(sz(hs) > 1){
                    dep[cur][i] = hs[1].f;
                }
                else{
                    dep[cur][i] = 0;
                }
            }
            for(int i : adj[cur]){
                if(i == par) continue;
                dfs2(i, cur, dfs2);
            }
        };
        dfs2(n - 1, -1, dfs2);
        vi dist(n);
        auto dfsdist = [&](int cur, int par, int d, auto &&dfsdist)->void{
            dist[cur] = d;
            for(int i : adj[cur]){
                if(i == par) continue;
                dfsdist(i, cur, d + 1, dfsdist);
            }
        };
        dfsdist(0, -1, 0, dfsdist);
        int lo = 0, hi = n;
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            vvi newadj(n);
            vector<unordered_map<int, int>> dp(n);
            // represents what happens when we are at node i, coming from node j
            // 0 - not processed
            // 1 - in stack
            // 2 - processed, no cycle
            // 3 - processed, cycle
            bool getstuck = false;
            rep(i, 0, n){
                for(auto [j, d] : dep[i]){
                    if(j == -1) continue;
                    if(d + 1 >= mid) newadj[j].pb(i);
                }
            }
            rep(i, 0, n){
                if(dist[i] <= mid){
                    newadj[i].clear();
                    for(int j : adj[i]){
                        if(dist[j] < dist[i]) newadj[i].pb(j);
                    }
                }
            }
            rep(i, 0, n){
                if(sz(newadj[i]) >= 3){
                    getstuck = true;
                }
                for(int j : newadj[i]){
                    dp[i][j] = 0;
                }
            }
            auto dfs3 = [&](int cur, int par, auto &&dfs3)->bool{
                if(sz(newadj[cur]) >= 3) return true;
                for(int i : newadj[cur]){
                    if(i == par) continue;
                    if(dfs3(i, cur, dfs3)) return true;
                }
                return false;
            };
            if(dfs3(n - 1, -1, dfs3)){
                lo = mid + 1;
            }
            else{
                hi = mid;
            }
        }
        cout << lo << nL;
    }
    
    return 0;
}
