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
    int n; cin >> n;
    vector<array<int, 3>> brackets(n);
    int tot = 0;
    rep(i, 0, n){
        string s; cin >> s;
        tot += sz(s);
        int minpref = 0;
        int delta = 0;
        for(char c : s) {
            delta += c == '(' ? 1 : -1;
            minpref = min(minpref, delta);
        }
        brackets[i] = {sz(s), minpref, delta};
    }
    
    sort(all(brackets), [&](array<int, 3> a, array<int, 3> b) {
        auto [sz1, minpref1, delta1] = a;
        auto [sz2, minpref2, delta2] = b;
        int min1 = min({minpref1, delta1 + minpref2});
        int min2 = min(minpref2, delta2 + minpref1);
        return min1 > min2;
    });
    vi dp(tot+1, -1e9);
    dp[0] = 0;
    rep(i, 0, n){
        auto [siz, minpref, delta] = brackets[i];
        vi new_dp(dp);
        rep(j, 0, sz(dp)) {
            if(j + minpref < 0) continue;
            if(j + delta >= sz(new_dp)) continue;
            new_dp[j + delta] = max(new_dp[j + delta], dp[j] + siz);
        }
        swap(dp, new_dp);
    }
    cout << dp[0] << "\n";
    
    return 0;
}