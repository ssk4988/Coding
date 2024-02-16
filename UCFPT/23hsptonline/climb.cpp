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
    int n; cin >> n;
    vi x(n), y(n);
    int mn = 0, mx = 0;
    rep(i, 0, n){
        cin >> x[i] >> y[i];
        if(y[i] < y[mn]) mn = i;
        if(y[i] > y[mx]) mx = i;
    }
    int lo = 0, hi = 2e7;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        vi v(n);
        auto dfs = [&](int cur, auto &&dfs)-> void {
            if(v[cur]) return;
            v[cur] = true;
            rep(i, 0, n){
                if((x[cur] - x[i]) * (x[cur] - x[i]) + (y[cur] - y[i]) * (y[cur] - y[i]) <= mid){
                    dfs(i, dfs);
                }
            }
        };
        dfs(mn, dfs);
        // cout << mid << " " << v[mx] << "\n";
        if(v[mx]) hi = mid;
        else lo = mid + 1;
    }
    // cout << mn << " " << mx << "\n";
    cout << fixed << setprecision(8) << sqrtl(lo) << '\n';
    
    return 0;
}