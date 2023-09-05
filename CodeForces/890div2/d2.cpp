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
    rep(cn, 5, 2001){
        ll n = cn;
        // cout << 5 * n * n << nL;
        ll cnt = 0;
        auto query = [&](ll l, ll r)->void{
            cnt += (r - l) * (r - l);
        };
        auto solve = [&](ll l, ll r, auto &solve)->void{
            if(l + 1 == r) return ;
            if(l + 2 == r){
                query(l, r - 1);
                return;
            }
            ll mid = l + (r - l) / 2;

            // ll cnt1 = (mid - 1 - l) * (mid - 1 - l) + (r - 1 - l) * (r - 1 - l);
            // cnt += cnt1;
            ll bestl = l;
            solve(l, mid, solve);
            ll bestr = mid;
            solve(mid, r, solve);
            // ll linv = 
            query(bestl, r - 1);
            if(bestl < r - 1)query(bestl + 1, r - 1);
            // ll rinv = query(bestr, r - 1) - (bestr < r - 1 ? query(bestr + 1, r - 1) : 0);
        };
        solve(0, n, solve);
        // cout << cnt << nL;
        cout << cnt << " " << 5 * n * n << nL;
        assert(cnt <= 5 * n * n);
    }
    
    return 0;
}
