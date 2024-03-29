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
    vl a(n), pw2(n);
    rep(i, 0, n){
        cin >> a[i];
        while(a[i] % 2 == 0){
            pw2[i]++;
            a[i] /= 2;
        }
    }
    vi dp(n+1, 1e9);
    dp[n] = 0;
    rep(i, 0, n){
        dp[i] = n - 1 - i;
    }
    for(int j = n - 1; j >= 0; j--){
        for(int i = j - 1; i >= 0; i--){
            if(a[i] % a[j] != 0) continue;
            int req;
            if(pw2[i] >= pw2[j]) {
                req = pw2[j] + 1;
            }
            else if(abs(j - i) != pw2[j] - pw2[i] && abs(j - i) < pw2[j] + 1){
                continue;
            }
            else req = abs(pw2[i] - pw2[j]);
            if(req > abs(j - i)) continue;
            dp[i] = min(dp[i], dp[j] + (j - i - 1));
        }
    }
    int ans = 1e9;
    rep(i, 0, n + 1){
        ans = min(ans, dp[i] + i);
    }
    cout << ans << "\n";
    
    return 0;
}
