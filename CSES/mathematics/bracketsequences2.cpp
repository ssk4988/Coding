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

const int LIM = 2e6 + 10;
ll inv[LIM];
ll fact[LIM];
ll invfact[LIM];
ll MOD = 1e9+7;

ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact[0] = invfact[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    rep(i,2,LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(i * fact[i - 1]);
        invfact[i] = mod(inv[i] * invfact[i - 1]);
    }
    auto choose = [&](int a, int b) -> ll{
        return mod(fact[a] * mod(invfact[a - b] * invfact[b]));
    };
    auto catalan = [&](int a)->ll{
        // if(a == 0) return 1;
        return mod(fact[2*a] * mod(mod(invfact[a] * invfact[a]) * inv[a + 1]));
    };
    int n; cin >> n;
    string str; cin >> str;
    if(n % 2 == 1){
        cout << 0 << nL;
        return 0;
    }
    int k = str.size();
    int col = 0, row = 0;
    rep(i, 0, k){
        if(str[i] == '(') col++;
        else row++;
        if(row > col){
            cout << 0 << nL;
            return 0;
        }
    }
    n /= 2;
    if(row > n || col > n){
        cout << 0 << nL;
        return 0;
    }
    int dr = n - row, dc = n - col;
    // if(col == row){
    //     cout << catalan(n - row) << nL;
    //     return 0;
    // }

    // ll ans = 0;
    // rep(i, col, n + 1){
    //     int dr = i - 1 - row;
    //     int dc = i - col;
    //     ll ways = dr + dc == 0 ? 1 : mod(choose(dr + dc, dc) - choose(dr + dc - 1, dc - 1));
    //     ans = mod(ans + mod(catalan(n - i) * ways));
    //     // cout << "from col " << i << ": there are " << mod(catalan(n - i) * ways) << nL;
    // }
    cout << mod(choose(n * 2 - (row + col), n - col) - choose(n * 2 - (row + col), n - 1 - col)) << nL;
    // cout << ans << nL;
    
    return 0;
}