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
        // vi d(n), s(n);
        vi traps(205, 10000);
        rep(i, 0, n){
            int d, s; cin >> d >> s;d--;
            traps[d] = min(traps[d], s);
        }
        int lo = 0, hi = 10000;
        while(lo < hi){
            int mid = lo + (hi - lo + 1) / 2;
            bool works = true;
            rep(i, 0, 1 + min(200, mid)){
                if((mid - i) * 2 >= traps[i]) works = false;
            }
            if(works) {
                lo = mid;
            }
            else hi = mid - 1;
        }
        cout << (lo+1) << nL;
    }
    
    return 0;
}