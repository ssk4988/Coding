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
        int n, a, b; cin >> n >> a >> b;
        vii ans;
        if(a + b < n) {
            for(int i = n; i > a+b; i--) {
                ans.pb({i, i});
            }
        }
        if(a + b > n) {
            cout << "NO\n";
            continue;
        }
        n = a+b;
        rep(i, 0, a) {
            ans.pb({a+b-i, a-i});
        }
        rep(i, 0, b) {
            ans.pb({i+1, a+1+i});
        }
        for(auto [x, y] : ans) {
            if(x>y) a--;
            if(x<y) b--;
        }
        if(a != 0 || b != 0) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        for(auto [x, y] : ans) {
            cout << x << " ";
        }
        cout << "\n";
        for(auto [x, y] : ans) {
            cout << y << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
