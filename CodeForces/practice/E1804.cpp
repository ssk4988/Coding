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
    vector<set<int>> sadj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
        sadj[a].insert(b);
        sadj[b].insert(a);
    }
    vector<vector<bool>> dp(1 << n, vector<bool>(n));
    queue<pi> states;
    rep(i, 0, n){
        states.push({1 << i, i});
        sort(all(adj[i]));
    }
    while(!states.empty()){
        pi cur = states.front();states.pop();
        if(dp[cur.f][cur.s]) continue;
        dp[cur.f][cur.s] = true;
        int firstbit = -1;
        rep(i, 0, n){
            if((cur.f & (1 << i)) > 0){
                firstbit = i;
                break;
            }
        }
        assert(firstbit != -1);
        for(int i : adj[cur.s]){
            if(i >= firstbit && (cur.f & (1 << i)) == 0){
                states.push({cur.f | (1 << i), i});
            }
        }
    }
    vi ans(n, -1);
    bool solved = false;
    int solvemask = -1;
    rep(i, 0, sz(dp)){
        if(solved) break;
        int firstbit = -1;
        rep(j, 0, n){
            if((i & (1 << j)) > 0){
                firstbit = j;
                break;
            }
        }
        rep(j, 0, n){
            if(dp[i][j] && sadj[j].count(firstbit)){
                vector<bool> canvisit(n);
                rep(k, 0, n){
                    if((i & (1 << k)) > 0){
                        canvisit[k] = true;
                        for(int l : adj[k]) canvisit[l] = true;
                    }
                }
                int vstcnt = 0;
                rep(k, 0, n){
                    vstcnt += canvisit[k];
                }
                if(vstcnt == n){
                    solved = true;
                    solvemask = i;
                    break;
                }
            }
        }
    }
    if(solvemask == -1) {
        cout << "No\n";
        return 0;
    }
    int cyclelen = 0;
    vi cur;
    rep(i, 0, n){
        if((solvemask & (1 << i))){
            cyclelen++;
            if(cyclelen == 1) cur.pb(i);
        }
    }
    auto dfs = [&](vi &cur, int mask, auto &&dfs)->bool{
        if(sz(cur) == cyclelen){
            return sadj[cur.back()].count(cur.front());
        }
        for(int i : adj[cur.back()]){
            if((solvemask & (1 << i)) > 0 && (mask & (1 << i)) == 0){
                cur.pb(i);
                if(dfs(cur, mask | (1 << i), dfs))
                    return true;
                cur.pop_back();
            }
        }
        return false;
    };
    dfs(cur, 1 << cur[0], dfs);
    rep(i, 0, sz(cur)){
        ans[cur[i]] = cur[(i + 1) % sz(cur)];
        for(int j : adj[cur[i]]){
            if(ans[j] == -1) ans[j] = cur[i];
        }
    }
    cout << "Yes\n";
    rep(i, 0, n){
        cout << (1 + ans[i]) << " ";
    }
    cout << nL;


    
    return 0;
}
