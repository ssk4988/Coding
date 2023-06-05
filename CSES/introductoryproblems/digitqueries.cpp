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
    int q; cin >> q;
    rep(cn, 0, q){
        ll k; cin >> k;
        k++; // 0
        ll cursum = 1; // 0
        ll curv = 1;
        int dig = 1;
        for(; true;curv *= 10){
            ll newsum = cursum + (9 * curv) * dig;
            if(newsum >= k) break;
            cursum = newsum;
            dig++;
        }
        ll newsum = cursum + 9 * curv * (dig);
        ll addnum = (k - cursum + dig - 1) / dig;
        ll num = curv - 1 + addnum;
        string str = to_string(num);
        cout << str[((k - 1 - cursum) % dig + dig) % dig] << nL;
    }
    
    return 0;
}
