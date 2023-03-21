#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;

#define nl '\n'
#define pb push_back
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i = a; i < b;i ++)
#define sz(x) (int)(x).size()

// #pragma GCC optimization("Ofast")

bool DEBUG = false;
int MOD = 1e9 + 7, BLANK = -1, m;

int maximum[5010];
int maxLen;
vector<vector<vvi>> dp;
int powt[5010];
 
int mod(int k, int mnum){
    return (k % mnum + mnum) % mnum;
}
int solve(int idx, int fmx_mod, int sum_mod, int eq)
{
    if(idx >= maxLen) return fmx_mod == 0;

    if(dp[eq][fmx_mod][sum_mod][idx] != BLANK) return dp[eq][fmx_mod][sum_mod][idx];

    int cap = (eq ? maximum[idx] : 9);
    int ans = 0;
    int dignum = maxLen - 1 - idx;
    for(int d = 0; d <= cap; d++)
    {
        // int new_f_mod = (f_mod + d * sum_mod) % m;
        int new_sum_mod = (sum_mod + d) % m;
        // int new_x_mod = (x_mod + ) % m;
        int new_fmx_mod = (fmx_mod + d * sum_mod - d * powt[dignum] + 10 * m) % m;
        ans = (ans + solve(idx + 1, new_fmx_mod, new_sum_mod, (eq && d >= maximum[idx]))) % MOD;
    }

    // if(DEBUG) cout << "\tdp(idx=" << idx << ", eq=" << eq << ", sum_mod=" << sum_mod << ", fmx_mod=" << fmx_mod << ") = " << ans << nl;
    return dp[eq][fmx_mod][sum_mod][idx] = ans;
}

void init(string &str)
{
    maxLen = str.size();
    dp = vector<vector<vvi>> (2, vector<vvi>(m, vvi(m, vi(str.size(), BLANK))));
    for(int i = 0; i < str.size(); i++) maximum[i] = str[i] - '0';
}

int isLGood()
{
    int f_mod = 0, sum_mod = 0, x_mod = 0;
    for(int i = maxLen - 1, ten = 1; i >= 0; i--)
    {
        int val = maximum[i];

        x_mod = ((val * ten) + x_mod) % m;
        f_mod = (f_mod + val * sum_mod) % m;
        sum_mod = (sum_mod + val) % m;
        ten = (ten * 10) % m;
    }

    // if(DEBUG) cout << "f_mod = " << f_mod << " x_mod=" << x_mod << nl;
    return f_mod == x_mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tt; cin >> tt;

    while(tt--)
    {
        string L, R;
        cin >> L >> R >> m;
        // if(DEBUG) cout << "-------------m=" << m << "--------------" << nl;
        powt[0] = 1;
        int len = 5 + max(L.length(), R.length());
        rep(i, 1, len){
            powt[i] = mod(powt[i - 1] * 10, m);
        }
        init(R);
        // if(DEBUG) 
        // {
        //     cout << "maximum r: "; for(int i : maximum) cout << i << " "; cout << endl;
        // }
        int ans = solve(0, 0, 0, 1);

        init(L);
        // if(DEBUG) 
        // {
        //     cout << "maximum l: "; for(int i : maximum) cout << i << " "; cout << endl;
        // }
        ans = (ans - solve(0, 0, 0, 1) + isLGood() + MOD) % MOD;
        // is L good?

        cout << ans << nl;
    }

    
}
