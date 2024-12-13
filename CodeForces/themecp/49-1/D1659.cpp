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
        vi a(n);
        vi b(n, 1);
        ll sm = 0;
        rep(i, 0, n){
            cin >> a[i];
            a[i] = n - a[i];
            sm += a[i];
        }
        int z = sm / n;
        for(int i = n-1; i >= 0; i--) {
            if(a[i] != 0){
                b[i] = 0;
                z--;
                a[z] -= n - i;
            }
        }
        rep(i, 0, n){
            cout << b[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
