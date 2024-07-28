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
        vi a(n * 2);
        rep(i, 0, n){ 
            cin >> a[i];
        }
        if(n % 2 == 0){
            int mn = INT_MAX, mx = INT_MIN;
            for(int i = 0; i < n; i += 2){
                vi b = {a[i], a[i+1], a[n + i], a[n + i + 1]};
                vi c = {b[0] + b[1], b[2] + b[3]};
                vi d = {b[0] + b[3], b[1] + b[2]};
                sort(all(c));
                sort(all(d));
                if(c[0] < d[0]){
                    swap(c, d);
                }
                mn = min(mn, c[0]);
                mx = max(mx, c[1]);
            }
            cout << (mx - mn) << "\n";
            continue;
        }
        vi order;
        order.pb(a[0]);
        order.pb(a[n]);
        int cur = n ^ 1;
        while(cur != 0){
            order.pb(a[cur]);
            if(cur >= n) cur -= n;
            else cur += n;
            order.pb(a[cur]);
            cur ^= 1;
        }
        rotate(order.begin(), order.begin() + 1, order.end());
        auto solve = [&](vi x) -> int {
            int mn = x[0] + x[1];
            int mx = mn;
            for(int i = 2; i < 2 * n; i += 2){
                if(i + 2 == 2 * n){
                    if(x[i] + x[i+1] < mn) return INT_MAX;
                }
            }
        };
    }
    
    return 0;
}
