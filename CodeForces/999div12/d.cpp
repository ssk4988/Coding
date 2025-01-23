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
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        map<int, int> freq; 
        rep(i, 0, n){
            int v; cin >> v; 
            freq[v]++;
        }
        bool works = true;
        auto dfs = [&](int u, auto &&dfs) -> bool {
            if(u < 1) return false;
            if(freq.count(u)) {
                freq[u]--;
                if(freq[u] == 0) freq.erase(u);
                return true;
            }
            if(u == 1) return false;
            int x = u/2;
            int y = u-x;
            if(dfs(x, dfs) && dfs(y, dfs)) return true;
            return false;
        };
        rep(i, 0, m) {
            int v; cin >> v;
            if(dfs(v, dfs)) {

            } else works = false;
        }
        if(sz(freq) > 0) works = false;
        cout <<(works ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
