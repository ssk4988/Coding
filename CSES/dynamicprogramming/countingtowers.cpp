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

ll MOD = 1e9 + 7;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int LIM = 1e6 + 10;
    vl precomp(LIM);
    precomp[0] = 1;
    ll sum1 = 1;
    ll sum3 = 1;
    rep(i, 1, LIM){
        precomp[i] = mod(sum1 + sum3);
        sum1 = mod(sum1 + precomp[i]);
        sum3 = mod(mod(3 * sum3) + precomp[i]);
    }
    int t; cin >> t;
    rep(i, 0, t){
        int n; cin >> n;
        cout << precomp[n] << nL;
    }
    
    return 0;
}
