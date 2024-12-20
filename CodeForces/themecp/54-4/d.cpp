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
        int n, k; cin >> n >> k;
        int mx = -1;
        rep(i, 1, n+1){
            cout << "? 1 " << i*n << endl;
            int t; cin >> t;
            if(t == n){
                mx = i;
                break;
            }
        }
        assert(mx != -1);
        // m/mx * k <= n
        // m/mx <= n/k
        bool done = false;
        rep(t, 1, 1 + n/k) {
            int m = mx * t;
            bool works = true;
            int cur = 1;
            rep(i, 0, k){
                if(cur > n){
                    works = false;
                    break;
                }
                cout << "? " << cur << " " << m << endl;
                int res; cin >> res;
                if(res == n+1){
                    works = false;
                    break;
                }
                cur = res+1;
            }
            if(works && cur == n+1){
                cout << "! " << m << endl;
                done = true;
                break;
            }
        }
        if(!done){
            cout << "! -1" << endl;
        }
        int res; cin >> res;
    }    
    
    return 0;
}
