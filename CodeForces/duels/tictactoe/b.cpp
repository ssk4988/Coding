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
    int n; ll d; cin >> n >> d;
    ll a, b; cin >> a >> b;
    vector<pll> c(n);
    rep(i, 0, n){
        ll x, y; cin >> x >> y;
        c[i] = {a * x + b* y, i};
    }
    sort(all(c));
    ll ans = 0;
    vi ids;
    rep(i, 0, n){
        if(d >= c[i].f){
            ans++;
            d -= c[i].f;
            ids.pb(c[i].s);
        }
    }
    cout << sz(ids) << "\n";
    for(int i : ids) cout << i+1 << " ";
    cout << "\n";
    
    return 0;
}
