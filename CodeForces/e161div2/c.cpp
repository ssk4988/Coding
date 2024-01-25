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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vvi cost(2, vi(n));
        rep(i, 0, n-1){
            if(i == 0 || a[i+1] - a[i] < a[i] - a[i-1]) cost[0][i+1] = cost[0][i] + 1;
            else cost[0][i+1] = cost[0][i] + a[i+1] - a[i];
        }
        for(int i = n - 1; i > 0; i--){
            if(i == n - 1 || a[i+1] - a[i] > a[i] - a[i-1]) cost[1][i-1] = cost[1][i] + 1;
            else cost[1][i-1] = cost[1][i] + a[i] - a[i-1];
        }
        int m; cin >> m;
        rep(i, 0, m){
            int x, y; cin >> x >> y; x--, y--;
            if(x < y){
                cout << (cost[0][y] - cost[0][x]) << nL;
            }
            else{
                cout << (cost[1][y] - cost[1][x]) << nL;
            }
        }
    }
    
    return 0;
}
