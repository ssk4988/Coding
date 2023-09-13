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
        vl a(n);
        ll lim = 1e18;
        ll sum = 0, prod = 1;
        rep(i, 0, n){
            cin >> a[i];
            sum += a[i];
            ll mult = (lim + prod - 1) / prod;
            if(mult <= a[i]){
                prod = lim;
            }
            else{
                prod *= a[i];
            }
        }
        if(prod >= lim){
            int left = 0, right = 0;
            while(a[left] == 1) left++;
            while(a[n - 1 - right] == 1) right++;
            cout << (left + 1) << " " << (n - 1 - right + 1) << nL;
            continue;
        }
        tuple<ll, int, int> best = {prod, 0, 0};
        vi inds;
        rep(i, 0, n){
            if(a[i] != 1) inds.pb(i);
        }
        for(int ix : inds){
            ll left = 0, right = 0, mid = 1;
            rep(i, 0, ix) left += a[i];
            for(int i = n - 1; i >= ix; i--){
                right += a[i];
            }
            for(int i = ix; i < n; i++){
                mid *= a[i];
                right -= a[i];
                best = max(best, {mid + left + right, ix, i});
            }
        }
        auto [score, l, r] = best;
        cout << (l + 1) << " " << (r + 1) << nL;
    }
    
    return 0;
}