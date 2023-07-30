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
    ll ans = 0;
    rep(i, 1, 1000000){
        string is = to_string(i);
        string is1(is);
        reverse(all(is1));
        if(!(is == is1)) continue;
        vi bs;
        int j = i;
        while(j){
            bs.pb(j % 2);
            j /= 2;
        }
        vi bs1(bs);
        reverse(all(bs1));
        if(bs == bs1){
            ans += i;
            cout << i << nL;
        }
    }
    cout << ans << nL;
    
    return 0;
}