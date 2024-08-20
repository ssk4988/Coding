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
    int nc; cin >> nc;
    auto nc2 = [](ll k)-> ll {
        return k * (k-1) / 2;
    };
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1){
            int a, b; cin >> a >> b;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi subsz(n, 1);
        vpi submin(n);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            submin[u] = {u, u};
            if(p != -1){
                adj[u].erase(find(all(adj[u]), p));
            }
            for(int v : adj[u]){
                dfs(v, u, dfs);
                submin[u] = min(submin[u], {submin[v].f, v});
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        vl ans(n+1);
        map<int, int> frontier; // min, endpos for it
        ll exc = 0;
        ll szsum = 0;
        set<int> mex;
        map<int, int> under;
        // add v to frontier from u
        auto addfrontier = [&](int v, int u) -> void {
            // cout << "add " << v << " to frontier from " << u << endl;
            under[u] += subsz[v];
            szsum += subsz[v];
            exc += nc2(subsz[v]);
            frontier[submin[v].f] = u;
        };
        // remove v from frontier from u
        auto remfrontier = [&](int v, int u) -> void {
            if(!frontier.count(submin[v].f)) return;
            // cout << "remove " << v << " from frontier" << endl;
            under[u] -= subsz[v];
            szsum -= subsz[v];
            exc -= nc2(subsz[v]);
            frontier.erase(submin[v].f);
        };
        for(int v : adj[0]){
            ans[0] += nc2(subsz[v]);
            addfrontier(v, 0);
        }
        ans[1] = nc2(n) - ans[0]; // path to everything else
        ans[1] = 0;
        ans[0] = nc2(n);
        rep(i, 1, n + 1){
            mex.insert(i);
        }
        set<int> endpos;
        endpos.insert(0);
        // handle 1 SOMEHOW
        int pre = 0;
        rep(i, 1, n + 1){
            if(!mex.count(i)) continue;
            if(sz(endpos) == 1){
                ans[i] = nc2(szsum) + szsum - exc + (sz(endpos) > 1);
            }
            else{
                // cout << "szsum: " << szsum << "\n";
                ans[i] = nc2(szsum) + szsum + (sz(endpos) > 1);
                for(int u : endpos){
                    ans[i] -= nc2(under[u]);
                }
            }
            ans[pre] -= ans[i];
            // cout << "mex is " << i << " was " << pre << " added " << ans[i] << " prev is " << ans[pre] << "\n";
            // cout << "current endpoints: ";
            // for(int u : endpos) cout << u << ":" << under[u] << " ";
            // cout << endl;
            pre = i;
            if(!frontier.count(i)) break; // not possible
            int rem = frontier[i];
            // cout << "remove from endpoints " << rem << "\n";
            int u = -1;
            for(int v : adj[rem]){
                // if(endpos.count(v));
                if(rem == 0 && sz(endpos) == 1){
                    if(submin[v].f == i) remfrontier(v, rem);
                }
                else remfrontier(v, rem);
                if(submin[v].f == i) u = v;
            }
            if(rem == 0 && sz(endpos) == 1){
                // do nothing
            }
            else endpos.erase(rem);
            while(u != i){
                mex.erase(u);
                for(int v : adj[u]){
                    if(submin[v].f == i){
                        u = v;
                        break;
                    }
                }
            }
            mex.erase(u);
            endpos.insert(u);
            for(int v : adj[u]){
                // cout << "add " << v << " to frontier\n";
                addfrontier(v, u);
            }
        }
        rep(i, 0, n+1){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}