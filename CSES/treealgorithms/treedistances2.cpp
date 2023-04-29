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


const int maxn = 2e5 + 10;
int n;
vi adj[maxn];
int subsz[maxn];
ll dsub[maxn];

void dfs(int cur, int pre){
    for(int i : adj[cur]){
        if(i == pre) continue;
        dfs(i, cur);
        subsz[cur] += subsz[i];
        dsub[cur] += dsub[i] + subsz[i];
    }
}

void dfs1(int cur, int pre){
    if(pre != -1){
        dsub[cur] = dsub[pre] - subsz[cur] + (n - subsz[cur]);
    }
    for(int i : adj[cur]){
        if(i == pre) continue;
        dfs1(i, cur);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    rep(i, 0, n) subsz[i] = 1;
    
    dfs(0, -1);
    dfs1(0, -1);
    rep(i, 0, n){
        cout << dsub[i] << " ";
    }
    cout << nL;
    
    return 0;
}