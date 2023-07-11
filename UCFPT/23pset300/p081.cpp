#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<vi> vvi;

#define nl '\n'
#define rep(i,a,b) for(int i = a; i < b; i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

const int DEBUG = false;
const ll MOD = 1e9 + 7;

vl dp;
vvi adj;
vi red;

void dfs(int node, int par)
{
    if(DEBUG) cout << "dfs(" << node << ")" << endl;

    vl store (dp.size());
    copy( all( dp ) , store.begin());

    for(int next : adj[node])
    {
        if(next == par) continue;

        dfs(next, node);
    }

    if(red[node])
    {
        for(int i = 0; i + 1 < dp.size(); i++)
            dp[i+1] = (dp[i+1] + store[i]) % MOD;
    }

    else
    {
        for(int i = 0; i < store.size(); i++)
            dp[i] = (dp[i] + store[i]) % MOD;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;

    adj = vvi (n);
    red = vi (n);

    int p, u; 
    for(int i = 1; i < n; i++) {
        cin >> p; 
        p--;

        adj[p].push_back(i);
    }

    for(int i = 0; i < m; i++) {
        cin >> u;
        u--;
        red[u] = true;
    }

    dp = vl (m + 1);
    dp[0] = 1;

    dfs(0, 0);

    for(int i = 0; i <= m;i ++)
        cout << dp[i] << nl;

}