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
        string l, r; cin >> l >> r;
        int forwarddiff = 0, backwarddiff = 0;
        rep(i, 0, n){
            forwarddiff += l[i] != r[i];
            backwarddiff += l[i] != r[n - 1 - i];
        }
        int fans = 0, bans = 0;
        if(forwarddiff == 0) fans = 0;
        else if(forwarddiff % 2 == 1) fans = forwarddiff * 2 - 1;
        else fans = forwarddiff * 2;

        if(backwarddiff == 0) bans = 2;
        else if(backwarddiff % 2 == 1) bans = 2 * backwarddiff;
        else bans = 2 * backwarddiff - 1;
        cout << min(bans, fans) << nL;
    }
    
    return 0;
}
