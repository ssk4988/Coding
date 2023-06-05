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
        int n, m; cin >> n >> m;
        set<int> x;
        x.insert(0); x.insert(m + 1);
        int left = 0, right = 0;
        rep(i, 0, n){
            int k; cin >> k;
            if(k == -1){
                left++;
            }
            else if(k == -2){
                right++;
            }
            else{
                x.insert(k);
            }
        }
        vi xs;
        for(int i : x) xs.pb(i);
        int best = 0;
        int l = 0, r = 0;
        rep(i, 0, sz(xs)){
            int lo = 0, hi = i;
            while(l < i && xs[i] - xs[l + 1] - abs(l + 1 - i) >= left) l++;
            if(r < i) r = i;
            while(r < sz(xs) - 1 && xs[r] - xs[i] - abs(r - i) < right) r++;
            int reqleft = min(xs[i] - xs[l] - abs(l - i), left);
            int reqright = min(xs[r] - xs[i] - abs(r - i), right);
            best = max(best, reqleft + reqright + sz(xs) - 2);
        }
        cout << best << nL;
        // cout << "ans for case " << (cn + 1) << ": " << best << nL;
    }
    
    return 0;
}
