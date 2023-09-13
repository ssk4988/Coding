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
         int x, y, n;
         cin >> x >> y >> n;
        vi res(n);
        res[n - 1] = y;
        int dif = 1;
        for(int i = n - 2; i >= 0; i--){
            res[i] = res[i + 1] - dif;
            dif++;
        }
        if(res[0] >= x){
            res[0] = x;
            rep(i, 0, n){
                cout << res[i] << " ";
            }
            cout << nL;
        }
        else{
            cout << "-1\n";
        }
    }
    
    return 0;
}