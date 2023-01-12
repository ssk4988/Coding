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

int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : adj[v])
    {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i)
    {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vector<char> label(n);
        adj = vvi(n, vi());
        rep(i, 0, n)
        {
            cin >> label[i];
        }
        rep(i, 0, n - 1){
            int a, b;
            cin >> a >> b;
            a--;b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        tin.clear();
        tout.clear();
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
        dfs(0, 0);
        vvi dp(n, vi(n, -1));
        auto solve = [&](int left, int right, auto &&solve) -> int {
            if(dp[left][right] != -1) return dp[left][right];
            if(left == right) return dp[left][right] = 1;
            int nleft, nright;
            if(is_ancestor(left, right)){
                // 1 below
                nleft = right;
                for(int i = l; i >= 0; i--){
                    if(is_ancestor(left, up[nleft][i]) && left != up[nleft][i]){
                        nleft = up[nleft][i];
                    }
                }
            }
            else{
                nleft = up[left][0];
            }
            int ans = 0;
            if(is_ancestor(right, left)){
                nright = left;
                for(int i = l; i >= 0; i--){
                    if(is_ancestor(right, up[nright][i]) && right != up[nright][i]){
                        nright = up[nright][i];
                    }
                }
            }
            else{
                nright = up[right][0];
            }
            if(label[left] == label[right]){
                if(nleft == right || nright == left) ans = 2;
                else ans = 2 + solve(nleft, nright, solve);
            }
            else{
                ans = max(solve(nleft, right, solve), solve(left, nright, solve));
            }
            return dp[left][right] = ans;
        };
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                ans = max(ans, solve(i, j, solve));
            }
        }
        cout << ans << nL;
    }

    return 0;
}