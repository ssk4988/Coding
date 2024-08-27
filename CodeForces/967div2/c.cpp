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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi p(n);
        auto query = [&](int u, int v) -> int {
            cout << "? " << u+1 << " " << v+1 << endl;
            int x; cin >> x; x--;
            return x;
        };
        rep(i, 1, n){
            int x;
            while((x = query(i, p[i])) != i) {
                p[i] = x;
            }
        }
        cout << "! ";
        rep(i, 1, n){
            cout << i+1 << " " << p[i]+1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}
