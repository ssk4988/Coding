#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll p; cin >> n >> p;
    vl c(n);
    ll pref = 0;
    int ans = n;
    rep(i,0, n){
        cin >> c[i];
        if(pref + (__uint128_t)(c[i]-1) * (i+1) >= p) {
            ans = i;
            break;
        }
        pref += c[i];
        if(pref > p) {
            ans = i+1; break;
        }
    }
    cout << ans << "\n";
    return 0;
}
