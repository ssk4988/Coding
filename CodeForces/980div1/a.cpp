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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vii a(n);
        rep(i, 0, n){
            cin >> a[i].f >> a[i].s;
        }
        sort(all(a), [](pii x, pii y) -> bool { 
            if(x.f > x.s) swap(x.f, x.s);
            if(y.f > y.s) swap(y.f, y.s);
            return x < y;
        });
        rep(i, 0,n) cout << a[i].f << " " << a[i].s << " ";
        cout <<"\n";
    }
    
    return 0;
}
