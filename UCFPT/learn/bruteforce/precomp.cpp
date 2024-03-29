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
        vi ans;
        auto go = [&](int val, int used, auto &&go) -> void {
            if(used > 0 && val % used != 0) return;
            if(used == n){
                ans.pb(val);
                return;
            }
            rep(i, used == 0, 10){
                go(val * 10 + i, used+1, go);
            }
        };
        go(0, 0, go);
        sort(all(ans));
        for(auto x : ans) cout << x << "\n";
    }
    
    return 0;
}
