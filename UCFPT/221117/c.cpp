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

#define maxN 2000005

int dp[maxN];
int greedy[maxN];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, -1, sizeof dp);
    memset(greedy, -1, sizeof greedy);
    int n;
    cin >> n;
    int c[n];
    rep(i, 0, n){
        cin >> c[i];
    }
    int lim = c[n - 1] + c[n - 2];
    greedy[0] = dp[0] = 0;
    greedy[1] = dp[1] = 1;
    for(int i = 0; i < n; i++){
        int next = i + 1 < n ? c[i + 1] : lim;
        for(int j = c[i]; j < next; j++){
            greedy[j] = 1 + greedy[j - c[i]];
        }
    }

    bool canon = true;
    for(int i = n - 1; i >= 0; i--) {
        int upb = lim + 1 - c[i];
        rep(j, 0, upb){
            if(dp[j] == -1) continue;
            if(dp[c[i] + j] == -1 || dp[c[i] + j] > dp[j] + 1){
                dp[c[i] + j] = dp[j] + 1;
            }
        }
    }
    rep(i, 0, lim){
        if(dp[i] != greedy[i]) canon = false;
    }
    cout << (canon ? "canonical" : "non-canonical") << nL;
    
    return 0;
}