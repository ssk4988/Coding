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
    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i] >> b[i];
    auto test = [&](int x) -> bool {
        int cur = 0, mn = 0, best = 0;
        int ans = 0;
        rep(i, 0, n){
            cur += (b[i] >= x) - (a[i] >= x);
            ans += a[i] >= x;
            mn =min(mn, cur);
            best = max(best, cur - mn);
        }
        return ans + best >= (n + 1) / 2;
    };
    int x = -1;
    for(int dif = 1 << 30; dif > 0; dif /= 2){
        if(test(x + dif)) x += dif;
    }
    cout << x << "\n";
    
    return 0;
}