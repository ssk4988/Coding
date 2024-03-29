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
        int n, d; cin >> n >> d;
        int ans = 0;
        vi days(n), pay(n);
        rep(i, 0, n){
            cin >> days[i] >> pay[i];
        }
        auto go = [&](int idx, int used, int prof, auto &&go) -> void {
            if(used > d) return;
            ans = max(ans, prof);
            if(idx == n || used == d) return;
            go(idx+1, used + days[idx], prof + pay[idx], go);
            go(idx+1, used, prof, go);
        };
        go(0, 0, 0, go);
        cout << ans << "\n";
    }
    
    return 0;
}
