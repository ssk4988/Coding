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
    vl smaller = {0, 1, 10, 100, 1000, 10000, 100000};
    vl bigger = {0, 9, 99, 999, 9999, 99999, 999999};
    rep(cn, 0, nc){
        int a, b, c; ll k; cin >> a >> b >> c >> k;
        int a1 = max(a, b);
        if(!(a1 == c || a1 + 1 == c)){
            cout << "-1\n";
            continue;
        }
        ll count = 0;
        bool found = false;
        vi ans;
        rep(i, smaller[a], bigger[a] + 1){
            if(count > k) break;
            int smallc = max(i + smaller[b], smaller[c]);
            int bigc = min(i + bigger[b], bigger[c]);
            if(smallc > bigger[c] || bigc < smaller[c] || bigc < smallc) continue;
            int num = bigc - smallc + 1;
            if(count < k && k <= count + num){
                // b in here
                int smallb = smallc - i, bigb = bigc - i;
                int bval = smallb + (k - count - 1);
                ans.pb(i);
                ans.pb(bval);
                ans.pb(i + bval);
                assert(smaller[b] <= bval && bval <= bigger[b]);
                assert(smaller[c] <= i + bval && i + bval <= bigger[c]);
                found = true;
                break;
            }
            count += num;
        }
        if(found){
            cout << ans[0] << " + " << ans[1] << " = " << ans[2] << nL;
        }
        else{
            cout << "-1\n";
        }
    }
    
    return 0;
}
