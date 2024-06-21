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
    rep(cn,0, nc){
        ll n, m; cin >> n >> m;
        ll h = n;
        cout << h << "\n";
        ll piece = 0;
        rep(i, 0, n){
            while(piece < m && piece * n <= m * (i+1)){
                cout << min(m * (i+1), (piece+1) * n) - piece * n << " " << i+1 << " ";
                cout << (piece+1) * n - min(m * (i+1), (piece+1) * n) << " " << (i+1)%n+1 << "\n";
                piece++;
            }
        }
        // ll cnt = 0;
        // rep(i, 0, m){
        //     ll low = i * n, high = (i+1) * n;
        //     while(m * (cnt+1) <= high) cnt++;
        //     cout << min(high, )
        // }
    }
    
    return 0;
}
