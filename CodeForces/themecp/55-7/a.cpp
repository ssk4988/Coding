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

vi factorize(int n) {
    vi res;
    for(int i = 2; i * i <= n; i++){
        while(n % i == 0){
            n /= i;
            res.pb(i);
        }
    }
    if(n > 1) res.pb(n);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int x, d; cin >> x >> d;
        int pd = 0;
        while(x % d == 0) {
            pd++;
            x /= d;
        }
        vi fs = factorize(x), dfs = factorize(d);
        if(sz(fs) >= 2 && pd >= 2){
            cout << "YES\n";
        } else if(sz(dfs) > 1 && pd >= 3 && !(pd == 3 && sz(fs) == 1 && fs[0] * fs[0] == d)) {
            cout << "YES\n";
        } else cout << "NO\n";
    }
    
    return 0;
}
