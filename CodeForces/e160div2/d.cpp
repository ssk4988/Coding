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

const ll MOD = 998244353;
inline ll mod(ll k){
    return k % MOD;
}
inline ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}
const int inf = 1e9 + 5;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n + 2, inf);
        rep(i, 1, n + 1){
            cin >> a[i];
        }
        vl dp(n + 2), pref(n + 2);
        dp[0] = pref[0] = 1;
        stack<pl> st;
        ll stsum = 0;
        st.push({dp[0], 0});
        stsum = mod(stsum + dp[0]);
        rep(i, 1, n + 2){
            while(sz(st) && a[st.top().s] > a[i]){
                stsum = mod1(stsum - dp[st.top().s]);
                st.pop();
            }
            dp[i] = mod(stsum + pref[i - 1]);
            if(sz(st)) dp[i] = mod1(dp[i] - pref[st.top().s]);
            if(sz(st) == 0 || a[st.top().s] < a[i]){
                st.push({dp[i], i});
                stsum = mod(stsum + dp[i]);
            }
            pref[i] = mod(dp[i] + pref[i - 1]);
        }
        cout << dp.back() << "\n";
    }
    
    return 0;
}
