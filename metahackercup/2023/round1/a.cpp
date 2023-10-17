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
        vd x(n);
        rep(i, 0, n){
            cin >> x[i];
        }
        sort(all(x));
        ld ans;
        auto score = [&](int i, int j)->ld{
            return abs(x[j] + x[i]) / 2;
        };
        // cout << "read case " << cn << nL;
        if(n == 5){
            ans = max(fabs(score(3, 4) - score(0, 2)), fabs(score(2, 4) - score(0, 1)));
        }
        else{
            ans = fabs(score(n - 2, n - 1) - score(0, 1));
        }
        cout << "Case #" << (cn + 1) << ": " << fixed << setprecision(8) << ans << "\n";
    }
    
    return 0;
}
