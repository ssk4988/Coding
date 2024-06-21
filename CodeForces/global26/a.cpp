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
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        bool found = false;
        rep(i, 0, n){
            if(a[i == 0 ? 1 : i-1] != a[i == n-1 ? n-2 : i+1]){
                cout << "YES\n";
                rep(j, 0, n){
                    cout << "BR"[i == j];
                }
                cout << "\n";
                found = true;
                break;
            }
        }
        if(!found) cout << "NO\n";
    }
    
    return 0;
}
