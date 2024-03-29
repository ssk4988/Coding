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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0,nc){
        int n; cin >> n;
        vi a(n);
        vi dp(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi c = a;
        sort(all(c));
        c.erase(unique(all(c)), c.end());
        vi freq(n), seen(n), span(n);
        vi carry(n); // can transfer to next guy
        vi ans(n); // actually can use
        vi full(n); // score for using all of it
        rep(i, 0, n){
            a[i] = lower_bound(all(c), a[i]) - c.begin();
            freq[a[i]]++;
        }
        rep(i, 0, n){
            if(seen[a[i]] == 0 && a[i]) full[a[i]] = carry[a[i]-1];
            if(seen[a[i]] == 0 && a[i]) span[a[i]] = dp[a[i]-1];
            full[a[i]]++;
            carry[a[i]]++;
            seen[a[i]]++;
            span[a[i]]++;
            dp[a[i]] = seen[a[i]];
            if(a[i]) dp[a[i]] = max(dp[a[i]], 1 + dp[a[i] - 1]);
            if(seen[a[i]] == freq[a[i]]) dp[a[i]] = max(dp[a[i]], span[a[i]]);
            if(seen[a[i]] == freq[a[i]]) carry[a[i]] = max(carry[a[i]], full[a[i]]);
            ans[a[i]] = max({ans[a[i]] + 1, carry[a[i]], full[a[i]], a[i] ? carry[a[i] - 1] + 1 : 0});
        }
        // int ans = max(*max_element(all(dp)), *max_element(all(span)));
        int val = *max_element(all(ans));
        cout << n - val << "\n";
    }
    
    return 0;
}
