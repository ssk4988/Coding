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
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b;
            a--,b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<vpi> qs(1);
        vi added(n);
        added[0] = true;
        for(int i : adj[0]){
            qs[0].pb({0, i});
        }
        int read = 0;
        while(read < qs.size()){
            int idx = 0;
            for(idx = 0; idx < qs[read].size(); idx++){
                auto [n1, n2] = qs[read][idx];
                if(added[n1] && !added[n2]){
                    added[n2] = true;
                    bool seen = false;
                    while(adj[n2].size()){
                        int v1 = adj[n2].back();
                        adj[n2].pop_back();
                        if(v1 == n1){
                            if(sz(qs) == read + 1) qs.pb({});
                            seen = true;
                        }
                        else{
                            if(!seen) qs[read].pb({n2, v1});
                            else qs[read + 1].pb({n2, v1});
                        }
                    }
                    // cout << "huh" << "\n";
                }
            }
            read++;
        }
        cout << (read - 1) << "\n";
    }
    
    return 0;
}
