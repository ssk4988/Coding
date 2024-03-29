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

const int N = 500;

using bs = bitset<N>;
using vb = array<bs, N>;
// [from][to]
vb col(vb &a){
    vb res;
    rep(i, 0, N){
        rep(j, 0, N){
            res[j][i] = a[i][j];
        }
    }
    return res;
}

vb operator*(vb &a, vb &b) {
    vb res;
    vb cols = col(b);
    rep(i, 0, N){
        rep(j, 0, N){
            res[i][j] = (a[i] & cols[j]).any();
        }
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vb> p(60), b(60);
    int m; cin >> m;
    rep(i, 0, m){
        int u, v, t; cin >> u >> v >> t; u--, v--;
        if(t) b[0][u][v] = 1;
        else p[0][u][v] = 1;
    }
    rep(i, 1, 60){
        p[i] = p[i-1] * b[i-1];
        b[i] = b[i-1] * p[i-1];
    }
    ll ans = 0; int pw = -1;
    vb cur;
    rep(i, 0, N){
        cur[i][i] = 1;
    }
    int par = 0;
    for(int i = 59; i >= 0; i--){
        vb nxt = cur * (par ? b : p)[i];
        if(nxt[0].any()){
            ans += 1LL << i;
            cur = nxt;
            par ^= 1;
        }
    }
    if(ans > 1e18) ans = -1;
    cout << ans << "\n";
    
    return 0;
}
