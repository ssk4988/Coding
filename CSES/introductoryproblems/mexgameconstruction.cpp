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
    int n; cin >> n;
    vvi a(n, vi(n));
    rep(i, 0, n) {
        rep(j, 0, n) {
            vi b;
            rep(k, 0, i) {
                b.pb(a[k][j]);
            }
            rep(k, 0, j) b.pb(a[i][k]);
            int mex = 0;
            sort(all(b));
            for(int v : b) if(v == mex) mex++;
            a[i][j] = mex;
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
