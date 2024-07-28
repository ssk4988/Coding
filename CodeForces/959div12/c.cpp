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
        int n; ll x; cin >> n >> x;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        partial_sum(all(a), a.begin());
        vi jmp(n, -1);
        vi score(n+1);
        for(int i = n-1; i >= 0; i--){
            auto it = lower_bound(all(a), (i == 0 ? 0 : a[i-1]) + x + 1);
            if(it != a.end()){
                jmp[i] = 1 + (it - a.begin());
                score[i] = 1 + score[jmp[i]];
            }
        }
        ll ans = 0;
        rep(i, 0, n) ans += n - i - score[i];
        cout << ans << "\n";
    }
    
    return 0;
}
