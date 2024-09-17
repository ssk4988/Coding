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
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vl ans(n);
    vector<map<int, int>> freq(n);
    auto dfs = [&](int cur, int pre, auto &&dfs)->void{
        freq[cur][a[cur]]++;
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs(i, cur, dfs);
            if(sz(freq[i]) > sz(freq[cur])) swap(freq[i], freq[cur]);
        }
        for(int i : adj[cur]){
            if(i == pre) continue;
            for(auto [key, val] : freq[i]) {
                freq[cur][key] += val;
            }
        }
        ans[cur] = sz(freq[cur]);
    };
    dfs(0, -1, dfs);
    rep(i, 0, n){
        cout << ans[i] << " ";
    }
    cout << nL;
    
    return 0;
}
