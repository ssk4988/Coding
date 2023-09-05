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
        int n; ll k; cin >> n >> k;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        ll lo = 0, hi = 1'000'000'000'010LL * 30001;
        while(lo < hi){
            ll mid = lo + (hi - lo + 1) / 2;
            vl a1(a);
            ll currows = 0;
            rep(i, 0, n){
                if(a1[i] >= mid){
                    currows += a1[i] / mid;
                    a1[i] %= mid;
                }
                if(i + 1 < n && a1[i] + a1[i + 1] >= mid){
                    currows += (a1[i] + a1[i + 1]) / mid;
                    if((a1[i] + a1[i + 1]) / mid > 0){
                        a1[i + 1] -= (a1[i] + a1[i + 1]) / mid * mid - a1[i];
                        a1[i] = 0;

                    }
                }
            }
            if(currows >= k){
                lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        cout << lo * k << nL;

    }
    
    return 0;
}
