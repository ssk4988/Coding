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
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi dep2(n);
    bool works = true;
    rep(i, 0, n){
        sort(all(adj[i]), [&](int a, int b)->bool{return sz(adj[a])<sz(adj[b]);});
        for(int j = sz(adj[i]) - 1; j >= 0 && sz(adj[adj[i][j]]) > 1 && dep2[i] < 3; j--){
            dep2[i]++;
        }
        if(dep2[i] >= 3){
            works = false;
            break;
        }
    }
    if(!works){
        cout << "No\n";
        return 0;
    }
    else{
        cout << "Yes\n";
        int best = 0;
        rep(i, 0, n){
            if(dep2[i] > dep2[best]) best = i;
        }
        vi ans;
        auto add = [&](int a)->void{
            ans.pb(a + 1);
        };
        auto dfs = [&](int cur, int pre, auto &&dfs)->void{
            add(cur);
            reverse(all(adj[cur]));
            int upb = sz(adj[cur]);
            if(pre == -1 && dep2[cur] > 1){
                swap(adj[cur][1], adj[cur].back());
                upb--;
            }
            rep(i1, 0, upb){
                int i = adj[cur][i1];
            // for(int i : adj[cur]){
                if(i == pre) continue;
                for(int j : adj[i]){
                    if(j == cur) continue;
                    dfs(j, i, dfs);
                }
                add(i);
            }
            if(pre == -1 && dep2[cur] > 1){
                dfs(adj[cur].back(), cur, dfs);
                swap(adj[cur][1], adj[cur].back());
            }
            reverse(all(adj[cur]));
        };
        dfs(best, -1, dfs);
        for(int i : ans)cout << i << " ";
        cout << nL;
    }

    
    return 0;
}
