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
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
    }
    vi visited(n);
    vi order;
    bool hascycle = false;
    // 0 not visited 1 in current dfs path 2 processed
    // returns whether to quit
    auto dfs = [&](int cur, int pre, auto &&dfs)->bool{
        visited[cur] = 1;
        for(int i : adj[cur]){
            if(i == pre) continue;
            if(visited[i] == 1){
                hascycle = true;
                return true;
            }
            if(visited[i] == 2) continue;
            if(dfs(i, cur, dfs)) return true;
        }

        visited[cur] = 2;
        order.pb(cur);
        return false;
    };
    rep(i, 0, n){
        if(visited[i] == 0 && dfs(i, -1, dfs)){
            break;
        }
    }
    reverse(all(order));
    vi revorder(n);
    rep(i, 0, sz(order)){
        revorder[order[i]] = i;
    }
    if(!hascycle){
        rep(i, 0, n){
            for(int j : adj[i]){
                if(revorder[j] < revorder[i]) hascycle = true;
            }
        }
    }
    if(hascycle){
        cout << "IMPOSSIBLE\n";
    }
    else{
        for(int i : order){
            cout << (i + 1) << " ";
        }
        cout << nL;
    }

    return 0;
}