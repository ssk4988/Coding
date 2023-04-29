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
    int n, q; cin >> n >> q;
    vi par(n + 1);
    par[0] = par[n] = n;
    rep(i, 1, n){
        cin >> par[i]; par[i]--;
    }
    vvi jump(25, vi(n + 1));
    jump[0] = par;
    rep(i, 1, 25){
        rep(j, 0, n + 1){
            jump[i][j] = jump[i - 1][jump[i - 1][j]];
        }
    }
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--;
        int cur = a;
        rep(j, 0, 25){
            if(b >> j & 1){
                cur = jump[j][cur];
            }
        }
        cout << (cur == n ? -1 : (cur + 1)) << nL;
    }
    
    return 0;
}