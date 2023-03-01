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
    int t, k; cin >> t >> k;
    // use ll for k?
    vector<vector<ld>> ncr(t + 1, vector<ld>(t + 1, 0));
    ncr[0][0] = 1;
    rep(i, 0, t){
        rep(j, 0, i + 1){
            ncr[i + 1][j] += ncr[i][j] / 2;
            ncr[i + 1][j + 1] += ncr[i][j] / 2;
        }
    }
    vector<ld> prefp(t + 1), suff(t + 5);
    rep(i, 1, t + 1){
        prefp[i] = prefp[i - 1] + ncr[t - 1][i - 1];
    }
    for(int i = t; i >= 1; i--){
        suff[i] = (i + 1 <= t ? suff[i + 1] : 0) + i * ncr[t - 1][i - 1];
    }
    auto nexte = [&](ld e) -> ld{
        if(e >= t) return e;
        ld sum = e * prefp[(int)e] + suff[((int)e) + 1];
        return sum;
    };
    auto predicte = [&](ld e, int project) -> ld{
        if(project == 0) return e;
        int e1 = (int) e;
        ld e2 = nexte(e);
        ld diff = e2 - e;
        return e + diff * (1 - powl(prefp[e1], project)) / (1 - prefp[e1]);
    };
    ld cure = suff[1];
    int kleft = k - 1;
    while(kleft > 0){
        int e1 = int(cure);
        int lo = 0, hi = kleft;
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            if(predicte(cure, mid) >= e1 + 1){
                hi = mid;
            }
            else{
                lo = mid + 1;
            }
        }
        cure = predicte(cure, lo);
        kleft -= lo;
    }
    cout << fixed << setprecision(8) << cure << nL;
    
    return 0;
}
