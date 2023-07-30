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
        if(n == 1){
            cout << "1\n";
        }
        else if(n == 2){
            cout << "2 1\n";
        }
        else{
            vi ans(n);
            ans[0] = 2;
            ans[n - 1] = 3;
            ans[n / 2] = 1;
            int cur = 4;
            rep(i, 0, n){
                if(ans[i] == 0) ans[i] = cur++;
            }
            rep(i, 0, n) cout << ans[i] << " ";
            cout << nL;
        }
    }
    
    return 0;
}
