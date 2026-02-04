#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vvi vis(4, vi(4));
    vector<string> grid(4);
    rep(i, 0, 4) {
        cin >> grid[i];
    }
    string word; cin >> word;
    auto dfs = [&](int i, int j, int k, auto &&dfs) -> bool {
        if(vis[i][j]) return false;
        if(word[k] != grid[i][j]) return false;
        vis[i][j] = 1;
        // cerr << i << " " << j << " " << k << endl;
        for(int i1 = i-1; i1 <= i+1; i1++) {
            for(int j1 = j-1; j1 <= j+1; j1++) {
                if(min(i1, j1) < 0 || max(i1, j1) >= 4) continue;
                if(k+1==sz(word) || dfs(i1, j1, k+1, dfs)) return true;
            }
        }
        vis[i][j] = 0;
        return false;
    };
    rep(i, 0, 4) {
        rep(j, 0, 4) {
            if(dfs(i, j, 0, dfs)) {
                cout << "POSSIBLE\n";
                return 0;
            }
        }
    }
                cout << "IMPOSSIBLE\n";
    
    
    return 0;
}
