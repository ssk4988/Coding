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
    
    string s;
    while(cin >> s) {
        assert(sz(s) <= 20);
        vi cnt(26);
        vi v;
        int n = sz(s);
        vvi suffs(n+1, vi(26));
        for(char c : s) {
            cnt[c-'a']++;
            v.pb(c-'a');
        }
        sort(all(v));
        vi mxs(n+1);
        for(int i = n-1; i >= 0; i--) {
            suffs[i] = suffs[i+1];
            suffs[i][v[i]]++;
            rep(j, 0, 26) {
                if(suffs[i][j] > suffs[i][mxs[i]]) mxs[i] = j;
            }
        }
        int ans = 0;
        auto dfs = [&](int idx, auto &&dfs) -> void {
            if(idx == sz(v)) {
                ans++;
                // if(ans % 1000000 == 0) cout << ans << endl;
                if(ans > 200000000) exit(0);
                return;
            }
            if(suffs[idx][mxs[idx]] + cnt[mxs[idx]] > n - idx) return;
            rep(i, 0, 26) {
                if(i == v[idx] || cnt[i] == 0) continue;
                cnt[i]--;
                dfs(idx+1, dfs);
                cnt[i]++;
            }
        };
        dfs(0, dfs);
        cout << ans << "\n";
    }
    
    return 0;
}
