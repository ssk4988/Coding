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
    rep(cn, 0, nc){
        int n; cin >> n;
        vi use(n+1);
        vi p(n);
        if(n & 1) {
            cout << n << "\n";
            p[n-1] = n;
            p[n-2] = n-1;
            p[n-3] = 3;
            p[n-4] = 1;
            rep(i, n-4, n) use[p[i]] = true;
        } else if(n == 6) {
            cout << "7\n";
            cout << "1 2 4 6 5 3\n";
            continue;
        } else {
            int b = 1 << __lg(n);
            cout << (2 * b - 1) << "\n";
            p[n-1] = b;
            p[n-2] = b-1;
            p[n-3] = b-2;
            p[n-4] = 3;
            p[n-5] = 1;
            rep(i, n-5, n) use[p[i]] = true;
        }
        int cur = 1;
        rep(i, 0, n){
            if(p[i]) continue;
            while(use[cur]) cur++;
            p[i] = cur;
            use[cur] = true;
        }
        rep(i, 0, n) cout << p[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
