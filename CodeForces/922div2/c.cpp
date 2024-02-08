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
        ll a, b, r; cin >> a >> b >> r;
        ll c = 1;
        for(; c * 2 <= a || c * 2 <= b; c *= 2);
        bool flip = false, abig = false;
        ll x = 0;
        while(c){
            ll ab = a & c, bb = b & c;
            if(ab != bb){
                if(!flip){
                    flip = true;
                    abig = ab > bb;
                }
                else if((x | c) <= r){
                    if(abig == (ab > bb))
                        x |= c;
                }
            }
            c /= 2;
        }
        cout << abs((a ^ x) - (b ^ x)) << nL;
    }
    
    return 0;
}
