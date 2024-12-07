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
    rep(cn, 0, nc){
        int n; cin >> n;
        string s; cin >> s;
        vi man(n);
        int l = -1, r = -1;
        rep(i, 0, n){
            if(r > i) {
                man[i] = min(r - i, man[l + r-i]);
            }
            while(i + man[i] < n && i-1 - man[i] >= 0 && s[i+man[i]] == s[i-1-man[i]]) man[i]++;
            if(i + man[i] > r) l = i-man[i], r = i+man[i];
        }
        vl dp(n+1);
        set<int> idxs;
        vvi buckets(n);
        rep(i, 0, n){
            if(man[i] > 0) buckets[i - man[i]].pb(i);
        }
        ll ans = 0;
        rep(i, 0, n){
            if(idxs.count(i)) idxs.erase(i);
            for(int v : buckets[i]) idxs.insert(v);
            if(sz(idxs)){
                int mn = *idxs.begin();
                dp[i + 2 * (mn - i)] += dp[i]+1;
            }
        }
        rep(i, 1, n+1) ans += dp[i];
        cout << ans << "\n";
    }
    
    return 0;
}
