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
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        ll ans = 0;
        rep(i, 0, n+1){
            ans += ll(i) * (n - i);
        }
        cout << ans << "\n";
        vpi st;
        st.push_back({1e9 + 10, -1});
        rep(i, 0, n){
            while(st.back() < pi{a[i], i}) st.pop_back();
            ll d = i - st.back().s - 1;
            // cout << i << " " <<  d << "\n";
            ans -= d * (d + 1) / 2;
            st.push_back({a[i], i});
        }
        cout << ans << "\n";
    }
    
    return 0;
}