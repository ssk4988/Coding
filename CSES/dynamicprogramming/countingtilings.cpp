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
using vvl = vector<vl>;

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

const ll MOD = 1e9 + 7;
const int maxn = 10;
const int maxm = 1000;
const int maxn2 = 1 << maxn;
vi trans[maxn2];
ll dp[maxm + 1][maxn2];
int n, m;

void bt(int mask, int mask2, int idx){
    if(idx == n){
        trans[mask].pb(mask2);
        return;
    }
    if(mask & (1 << idx)){
        // is closed now;
        bt(mask, mask2, idx + 1);
    }
    else{
        // can open now
        bt(mask, mask2 | (1 << idx), idx + 1);

        // group 2
        if(idx + 1 < n && (mask & (1 << (idx + 1))) == 0){
            bt(mask, mask2, idx + 2);
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    int n2 = 1 << n;
    
    rep(i, 0, n2){
        bt(i, 0, 0);
    }
    int sum = 0;
    rep(i, 0, n2){
        sum += sz(trans[i]);
    }
    dp[0][0] = 1;
    rep(i, 0, m){
        rep(j, 0, n2){
            if(dp[i][j] == 0) continue;
            for(int j2 : trans[j]){
                dp[i + 1][j2] += dp[i][j];
                if(dp[i + 1][j2] >= MOD) dp[i + 1][j2] -= MOD;
            }
        }
    }
    cout << dp[m][0] << nL;
    
    return 0;
}