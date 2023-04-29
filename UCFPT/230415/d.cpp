#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<vl> vvl;

#define rep(i,a,b) for(int i = a; i < b;i ++)
#define nl '\n'
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back

vvl slope, constant, timer;
vl height;
int n, tq;
vector<set<int>> adj;
vector<bool> markedsubtree;
vl grass;
bool cmp(int a, int b){
    return 2 * slope[b][0] + slope[b][0] * timer[b][0] < 2 * slope[a][0] + slope[a][0] * timer[a][0];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> tq;
    adj.resize(n);
    grass.resize(n);
    rep(i, 1, n){
        int a, b; cin >> a >> b; a--;
        // adj[i].insert(a);
        adj[a].insert(i);
        grass[i] = b;
    }
    height.resize(n);
    markedsubtree.resize(n);
    vvi calc(n, vi(2));
    slope = vvl(n, vl(2)), constant = vvl(n, vl(2)), timer = vvl(n, vl(2));
    // auto dfs = [&](int cur, int par, auto &&dfs)->void{
    //     if(par != -1) adj[cur].erase(par);
    //     for(int i : adj[cur]){
    //         dfs(i, cur, dfs);
    //     }
    // };
    // dfs(0, -1, dfs);
    auto maxHeight = [&](int cur, int dist, auto && maxHeight) -> ll{
        height[cur] = dist;
        ll best = dist;
        for(int i : adj[cur]){
            best = max(best, maxHeight(i, dist + 1, maxHeight));
        }
        return best;
    };
    int mxh = maxHeight(0, 0, maxHeight);
    auto mark = [&](int cur, auto &&mark)->bool{
        if(height[cur] == mxh) {
            markedsubtree[cur] = true;
        }
        for(int i : adj[cur]){
            if(mark(i, mark)){
                markedsubtree[cur] = true;
            }
        }
        return markedsubtree[cur];
    };
    mark(0, mark);
    auto solve = [&](int cur, int terminal, auto &&solve)->void{
        if(calc[cur][terminal])return;
        calc[cur][terminal] = true;
        vi childs;
        for(int i : adj[cur]){
            childs.pb(i);
            solve(i, 0, solve);
        }
        if(terminal == 0){
            slope[cur][terminal] = grass[cur];
            sort(all(childs), cmp);
            if(childs.size() == 0) return;
            timer[cur][terminal] = 1;
            for(int i : childs){
                slope[cur][terminal] += slope[i][terminal];
                constant[cur][terminal] += constant[i][terminal] + slope[i][terminal] * timer[cur][terminal];
                timer[cur][terminal] += 2 + timer[i][terminal];
            }
            timer[cur][terminal]--; 
            return;
        }
        else{
            solve(cur, 0, solve);
            slope[cur][1] = slope[cur][0];
            constant[cur][1] = -1;
            timer[cur][1] = -1;
        }
        vl suff(sz(childs));
        vl timerpref(sz(childs));
        for(int i = sz(childs) - 1; i >= 0; i--){
            suff[i] = slope[childs[i]][0] + 2;
            if(i + 1 < sz(childs)){
                suff[i] += suff[i + 1];
            }
        }
        rep(i, 0, sz(childs)){
            timerpref[i] = timer[childs[i]][0];
            if(i > 0) timerpref[i] += timer[childs[i - 1]][0];
        }
    
        rep(i, 0, sz(childs)){
            solve(childs[i], 0, solve);
            if(!markedsubtree[childs[i]]) continue;
            solve(childs[i], 1, solve);
            ll newtimer = timer[cur][0] + timer[childs[i]][1] - timer[childs[i]][0];
            ll newconstant = constant[cur][0] - (i + 1 < sz(childs) ? suff[i + 1] : 0) * timer[childs[i]][0] + (slope[i][0] * (sz(childs) - 1 - i + timerpref.back() - timerpref[i]));
            if(constant[cur][1] == -1 || newconstant < constant[cur][1]){
                timer[cur][1] = newtimer;
                constant[cur][1] = newconstant;
            }
        }
    };
    solve(0, 0, solve);
    solve(0, 1, solve);
    if(tq == 0){
        cout << timer[0][0] << " " << (constant[0][0]) << nl;
    }
    else{

        cout << (timer[0][1]) << " " << (constant[0][1]) << nl;
        // assert(timer[0][0] - mxh == timer[0][1]);
    }
    
}