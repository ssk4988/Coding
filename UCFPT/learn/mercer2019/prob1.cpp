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
    

    while(true) {
        int n, m, k; cin >> m >> n >> k;
        using state = tuple<int, int, int>;
        set<state> seen;
        priority_queue<pair<int, state>, vector<pair<int, state>>, greater<>> pq;
        if(n == -1) break;
        n++, m++;
        vvi mud(n, vi(m));
        vi len(k);
        rep(i, 0, k) cin >> len[i];
        rep(i, 0, n) {
            rep(j, 0, m) cin >> mud[i][j];
        }
        reverse(all(mud));
        pq.push({mud[0][0], {0, 0, 0}});
        int ans = -1;
        vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
        while(sz(pq)) {
            auto [d, tup] = pq.top(); pq.pop();
            auto [i,j,mask] = tup;
            if(i==n-1 && j==m-1) {
                ans = d;
                break;
            }
            if(seen.count(tup)) continue;
            seen.insert(tup);
            rep(t, 0, 4) {
                int i1 = i + dr[t], j1 = j + dc[t];
                if(min(i1, j1) < 0 || i1 >= n || j1 >= m) continue;
                pq.push({d+mud[i1][j1], {i1, j1, mask}});
            }
            rep(t, 0, k) {
                if((mask >> t)&1) continue;
                rep(i1, 0, n) {
                    rep(j1, 0, m) {
                        if((i1-i)*(i1-i)+(j1-j)*(j1-j) == len[t]*len[t]) {
                            pq.push({d+mud[i1][j1], {i1, j1, mask ^ (1 << t)}});
                        }
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
