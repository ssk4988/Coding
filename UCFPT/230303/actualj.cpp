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

bool DEBUG = false;
ll MOD = 1e9 + 7, BLANK = -1, m;

vi maximum;
vector<vector<map<int, ll>>> dp;
vl powt;

ll mod(ll k, ll mnum){
    return (k % mnum + mnum) % mnum;
}

ll solve(int idx, int fmx_mod, int sum_mod, int eq)
{
    if(idx >= maximum.size()) return (fmx_mod == 0) ? 1 : 0;
    int key = sum_mod * m + fmx_mod;

    if(dp[idx][eq].find(key) != dp[idx][eq].end()) return dp[idx][eq][key];

    int cap = (eq ? maximum[idx] : 9);
    ll ans = 0;
    int dignum = maximum.size() - 1 - idx;
    for(int d = 0; d <= cap; d++)
    {
        int new_sum_mod = mod(sum_mod + d, m);
        int new_fmx_mod = mod(mod(fmx_mod + d * sum_mod, m) - d * powt[dignum], m);
        ans = (ans + solve(idx + 1, new_fmx_mod, new_sum_mod, (eq && d >= maximum[idx]))) % MOD;
    }

    if(DEBUG) cout << "\tdp(idx=" << idx << ", eq=" << eq << ", sum_mod=" << sum_mod << ", fmx_mod=" << fmx_mod << ") = " << ans << nl;
    return dp[idx][eq][key] = ans;
}

void init(string &str)
{
    maximum = vi (str.size());
    dp = vector<vector<map<int, ll>>> (str.size(), vector<map<int, ll>> (2));
    for(int i = 0; i < str.size(); i++) maximum[i] = str[i] - '0';
}

int isLGood()
{
    int f_mod = 0, sum_mod = 0, x_mod = 0;
    for(int i = maximum.size() - 1, ten = 1; i >= 0; i--)
    {
        int val = maximum[i];

        x_mod = ((val * ten) + x_mod) % m;
        f_mod = (f_mod + val * sum_mod) % m;
        sum_mod = (sum_mod + val) % m;
        ten = (ten * 10) % m;
    }

    if(DEBUG) cout << "f_mod = " << f_mod << " x_mod=" << x_mod << nl;
    return (f_mod == x_mod) ? 1 : 0;
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
        powt.pb(1);
        int len = 5 + max(L.length(), R.length());
        rep(i, 0, len){
            powt.pb(mod(powt.back() * 10, m));
        }
        if(DEBUG) cout << "-------------m=" << m << "--------------" << nl;

        init(R);
        if(DEBUG) 
        {
            cout << "maximum r: "; for(int i : maximum) cout << i << " "; cout << endl;
        }
        ll ans = solve(0, 0, 0, 1);

        init(L);
        if(DEBUG) 
        {
            cout << "maximum l: "; for(int i : maximum) cout << i << " "; cout << endl;
        }
        ans = (ans - solve(0, 0, 0, 1) + isLGood() + MOD) % MOD;
        // is L good?

        cout << ans << nl;
    }

    
}
