#include <bits/stdc++.h>
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
    vvi g(20, vi(20));
    rep(i, 0, 20){
        rep(j, 0, 20) cin >> g[i][j];
    }
    ll best = 0;
    rep(i, 0, 21 - 4){
        rep(j, 0, 20){
            ll k1 = 1;
            rep(k, 0, 4) k1 *= g[i + k][j];
            best = max(best, k1);
            k1 = 1;
            rep(k, 0, 4) k1 *= g[j][i + k];
            best = max(best, k1);
        }
    }
    rep(i, 0, 21 - 4){
        rep(j, 0, 21 - 4){
            ll k1 = 1;
            rep(k, 0, 4) k1 *= g[i + k][j + k];
            best = max(best, k1);
            k1 = 1;
            rep(k, 0, 4) k1 *= g[i + k][19 - (j + k)];
            best = max(best, k1);
        }
    }
    cout << best << nL;
    
    return 0;
}
