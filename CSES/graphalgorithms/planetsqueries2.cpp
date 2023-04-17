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
    int n, q; cin >> n >> q;
    vi a(n);
    vvi jump(32, vi(n));
    rep(i, 0, n){
        cin >> a[i];
        a[i]--;
        jump[0][i] = a[i];
    }
    rep(i, 1, 32){
        rep(j, 0, n){
            jump[i][j] = jump[i - 1][jump[i - 1][j]];
        }
    }
    auto getKth = [&](int x, int k)->int{
        int cur = x;
        rep(j, 0, 32){
            if((1 << j) & k) cur = jump[j][cur];
        }
        return cur;
    };
    vi cyclenum(n, -1), disttocycle(n), visited(n), indcycle(n, -1), nodeincycle(n, -1);
    vvi cycles;
    int numcycles = 0;
    auto dfs = [&](int cur, vi &path, set<int> curpath, auto &&dfs)->void{
        if(visited[a[cur]]){
            disttocycle[cur] = 1 + disttocycle[a[cur]];
            nodeincycle[cur] = nodeincycle[a[cur]];
            cyclenum[cur] = cyclenum[a[cur]];
            visited[cur] = true;
            return;
        }
        if(curpath.count(cur)){
            bool seenself = false;
            cycles.pb({});

            for(int i = sz(path) - 1; i >= 0; i--){
                if(!seenself){ 
                    cyclenum[path[i]] = numcycles;
                    cycles.back().pb(path[i]);
                    nodeincycle[path[i]] = path[i];
                }
                else{
                    disttocycle[path[i]] = 1 + disttocycle[path[i + 1]];
                    nodeincycle[path[i]] = nodeincycle[path[i + 1]];
                }
                if(path[i] == cur)seenself = true;
                cyclenum[path[i]] = numcycles;
            }
            reverse(all(cycles.back()));
            rep(i, 0, sz(cycles.back())){
                indcycle[cycles.back()[i]] = i;
            }
            numcycles++;
            visited[cur] = true;
            return;
        }

        curpath.insert(cur);
        path.pb(cur);
        dfs(a[cur], path, curpath, dfs);
        path.pop_back();
        curpath.erase(cur);
        visited[cur] = true;

        return;
    };
    vi path;
    set<int> curpath;
    rep(i, 0, n){
        if(!visited[i]){
            curpath.clear();path.clear();
            dfs(i, path, curpath, dfs);
        }
    }
    auto distto = [&](int l, int r)->int{
        if(indcycle[l] <= indcycle[r])return indcycle[r] - indcycle[l];
        return sz(cycles[cyclenum[l]]) + indcycle[r] - indcycle[l];
    };
    rep(i, 0, q){
        int a, b; cin >> a >> b;a--,b--;
        int res;
        if(cyclenum[a] != cyclenum[b]){
            cout << "-1\n";continue;
        }
        if(indcycle[a] == -1 && indcycle[b] == -1){
            if(nodeincycle[a] != nodeincycle[b] || disttocycle[a] < disttocycle[b]){
                cout << "-1\n";continue;
            }
            res =  (disttocycle[a] - disttocycle[b]);
        }
        else if(indcycle[a] == -1 && indcycle[b] != -1){
            res = (disttocycle[a] + distto(nodeincycle[a], b));
        }
        else if(indcycle[a] != -1 && indcycle[b] == -1){
            cout << "-1\n";continue;
        }
        else{
            res = distto(a, b);
        }
        cout << (getKth(a, res) == b ? res : -1) << nL;
    }
    
    return 0;
}
