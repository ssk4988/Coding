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

using uint = unsigned int;
uint x, y, z;
uint rng61(){
    x = x ^ (x << 11);
    x = x ^ (x >> 4);
    x = x ^ (x << 5);
    x = x ^ (x >> 14);
    uint w = x ^ (y ^ z);
    x = y;
    y = z;
    z = w;
    return z;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        cin >> x >> y >> z;
        vvi sparse(__lg(n) + 1, vi(n));
        rep(i, 0, m){
            uint l = rng61(), r = rng61(), v = rng61();
            l %= n;
            r %= n;
            if(l > r) swap(l, r);
            r++;
            v %= 1 << 30;
            int p = __lg(r - l);
            sparse[p][l] = max(sparse[p][l], int(v));
            sparse[p][r - (1 << p)] = max(sparse[p][r - (1 << p)], int(v));
        }
        for(int i = sz(sparse) - 1; i > 0; i--){
            rep(j, 0, n){
                if(j + (1 << i) > n) continue;
                sparse[i-1][j] = max(sparse[i-1][j], sparse[i][j]);
                sparse[i-1][j + (1 << (i-1))] = max(sparse[i-1][j + (1 << (i-1))], sparse[i][j]);
            }
        }
        ll ans = 0;
        rep(i, 0, n){
            ans ^= ll(i+1) * sparse[0][i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
