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

const int N = 805;
int dp[N];
int rem[N][N]; // min ops to left to delete l,r range
int a[N];
int n;

const int oo = 1e9;

int gorem(int l, int r) {
    if(l > r) return 0;
    int &ans = rem[l][r];
    if(ans != -1) return ans;
    ans = oo;
    if((l - a[l]) % 2 == 1 || a[l] > l) return ans;
    const int k = (l - a[l]) / 2;
    for(int m = l+1; m <= r; m += 2) {
        int x = gorem(l+1, m-1);
        int y = gorem(m+1, r);
        if(x > k) continue;
        ans = min(ans, max({k, y - (r-m)/2}));
        // ans = max(ans, 1 + x + go(m+1, r, 1+x + k));
    }
    // cout << "rem [" << l << "," << r << "] = " << ans << endl;
    return ans;
}

int go(int idx) {
    int &ans = dp[idx];
    if(ans != -1) return ans;
    ans = go(idx-1);
    rep(l, 0, idx){
        if(go(l) >= gorem(l, idx-1)) ans = max(ans, (idx - l)/2 + go(l));
    }
    // cout << "dp " << idx << " = " << ans << endl;
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        cin >> n;
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
        }
        memset(rem, -1, sizeof rem);
        memset(dp, -1, sizeof dp);
        dp[0] = 0;

        int ans = go(n);
        cout << ans << "\n";
    }
    
    return 0;
}
