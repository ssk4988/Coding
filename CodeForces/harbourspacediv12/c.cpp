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
        ll x; cin >> x;
        vl seq;
        seq.pb(x);
        while(x > 1){
            if(__builtin_popcount(x) == 1){
                x /= 2;
            }
            else{
                ll x1 = x;
                int shift = 0;
                while((x1 & 1) == 0){
                    x1 >>= 1;
                    shift++;
                }
                x -= (1LL) << shift;
            }
            seq.pb(x);
        }
        cout << sz(seq) << nL;
        for(ll i : seq) cout << i << " ";
        cout << nL;
    }
    
    return 0;
}