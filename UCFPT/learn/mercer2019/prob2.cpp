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
        for(char c : s) {
            cnt[c-'a']++;
            v.pb(c-'a');
        }
        sort(all(v));
        int ans = 0;
        vl dp(1 << n, 0);
        dp[0] = 1;
        rep(mask, 0, sz(dp)) {
            int used = __builtin_popcount(mask);
            vi seen(26);
            rep(i, 0, n) {
                if((mask >> i)&1) continue;
                if(v[used] == v[i] || seen[v[i]]) continue;
                seen[v[i]] = 1;
                dp[mask | (1 << i)] += dp[mask];
            }
        }
        cout << dp.back() << "\n";
    }
    
    return 0;
}
