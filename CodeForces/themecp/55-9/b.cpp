#include <bits/stdc++.h>
#include <bit>
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
        int n; cin >> n;
        vvi child(n);
        rep(i, 1, n){
            int p; cin >> p; p--;
            child[p].pb(i);
        }
        auto dfs = [&](int u, auto &&dfs) -> int {
            priority_queue<int, vi, greater<>> pq;
            int mx = 0;
            for(int v : child[u]) {
                int x = dfs(v, dfs);
                pq.push(x);
                mx = max(mx, x);
            }
            if(sz(pq) == 0) return 0;
            while(sz(pq) > 1) {
                int i1 = pq.top(); pq.pop();
                int i2 = pq.top(); pq.pop();
                pq.push(max(i1, i2)+1);
            }
            return max(1+mx, pq.top());
            // assert(false);
        };
        auto dep= dfs(0, dfs);
        cout << dep << "\n";
        
    }
    
    return 0;
}
