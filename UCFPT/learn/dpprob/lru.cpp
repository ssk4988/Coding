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
    int n, k; cin >> n >> k;
    vd a(n), dp(1 << n), ans(n);
    dp[0] = 1;
    int pos = 0;
    rep(i, 0, n){ 
        cin >> a[i];
        if(a[i] > 0) pos++;
    }
    k = min(pos, k);
    rep(i, 0, 1 << n){
        int cnt = 0;
        ld sum = 0;
        rep(j, 0, n){
            if(i & (1 << j)){
                cnt++;
            }
            else{
                sum += a[j];
            }
        }
        // if(sum )
        rep(j,0,n){
            if((i & (1 << j)) == 0){
                if(sum > 0)dp[i | (1 << j)] += a[j] / sum * dp[i];
            }
            else{
                if(cnt == k) ans[j] += dp[i];
            }
        }
    }
    rep(i, 0, n) cout << fixed << setprecision(8) << ans[i] << " ";
    cout << nL;
    return 0;
}
