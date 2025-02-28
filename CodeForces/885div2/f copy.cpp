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
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        map<vi, int> seen;
        seen[a] = 0;
        int t = 0;
        bool cycle = false;
        while(accumulate(all(a), 0)) {
            t++;
            vi b(a);
            rep(i, 0, n) b[i] ^= a[(i+1)%n];
            a = b;
            if(seen.count(a)) {
                cout << "cycled in " << t-seen[a] << endl;
                cycle = true;
                break;
            }
            seen[a] = t;
            rep(i, 0, n) cout << a[i] << " ";
            cout << "\n";
        }
        if(!cycle) cout << "done in " << t << endl;
    }
    
    return 0;
}
