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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ld a, b; cin >> a >> b;
    ld lo = 0, hi = 100;
    rep(_, 0, 50) {
        ld md = (lo+hi)/2;
        ld val = exp(-a * md) + exp(-b * md);
        if(val < 1) hi = md;
        else lo = md;
    }
    cout << fixed << setprecision(10) << lo << "\n";
    
    
    return 0;
}
