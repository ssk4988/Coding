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

using vvl = vector<vl>;
const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p/2);
    res = mod(res * res);
    if(p % 2 == 1) res = mod(res * b);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n = 5000;
    cin >> n;
    vvl sterling(n + 1, vl(n + 1)), chooses(n + 1, vl(n + 1));
    chooses[0][0] = 1;
    sterling[0][0] = 1;
    rep(i, 1, n + 1){
        rep(j, 1, n + 1){
            sterling[i][j] = mod(mod((i-1) * sterling[i - 1][j]) + sterling[i - 1][j - 1]);
        }
        rep(j, 1, i){
            chooses[i][j] = chooses[i][j] + chooses[i - 1][j - 1];
            chooses[i][j] = chooses[i][j] + chooses[i - 1][j];
            if(chooses[i][j] >= MOD) chooses[i][j] %= MOD;
        }
        chooses[i][0] = chooses[i][i] = 1;
    }
    vl ans(n + 1);
    vl pows(n + 1);
    pows[0] = 1;
    rep(i, 1, sz(pows)) pows[i] = mod(n * pows[i - 1]);
    rep(k, 1, n + 1){
        rep(a, k, n + 1){
            ans[k] = mod(ans[k] + mod(sterling[a][k] * mod(chooses[n - 1][a - 1] * pows[n - a])));
        }
        cout << ans[k] << "\n";
    }

    
    return 0;
}
