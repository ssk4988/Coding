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

const int N = 2e5+10;
using bs = bitset<N>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        k = min(n-k, k); // irrelevant
        vvi child(n);
        vi par(n, -1), depth(n);
        rep(i, 1, n) {
            cin >> par[i]; par[i]--;
            depth[i] = 1 + depth[par[i]];
            child[par[i]].push_back(i);
        }
        int mindepth = n;
        rep(i, 0, n) {
            if(sz(child[i]) == 0) mindepth = min(mindepth, depth[i]);
        }
        vi cnt(mindepth+2);
        rep(i, 0, n) {
            cnt[min(mindepth+1, depth[i])]++;
        }
        // cerr << "k: " << k << endl;
        // cerr << "mindepth: " << mindepth << endl;
        // rep(i, 0, sz(cnt)) cerr << i << " " << cnt[i] << endl;
        int ans = mindepth+1;
        bs cur;
        cur[0] = 1;
        // int left = n;
        rep(i, 0, mindepth+1) {
            // left -= cnt[i];
            cur |= cur << cnt[i];
            // int start = max(0, k-left);
            // int idx = cur._Find_next(start-1);
            // if(idx <= k) {
            //     ans = max(ans, i+1);
            // }
        }
        int start = max(0, k-(cnt.back()));
        int idx = cur._Find_next(start-1);
        if(idx > k) ans--;
        cout << ans << "\n";
    }
    
    return 0;
}
