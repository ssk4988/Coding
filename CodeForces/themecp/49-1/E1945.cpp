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
        int n, x; cin >> n >> x; x--;
        vi p(n);
        rep(i, 0, n){
            cin >> p[i]; p[i]--;
        }
        int l = 0, r = n;
        vi use(n), tp(n);
        while(r-l > 1) {
            int m = (r+l)/2;
            use[m] = true;
            tp[m] = p[m] <= x;
            if(p[m] <= x) {
                l = m;
            } else r = m;
        }
        vii moves;
        if(p[l] != x) {
            int idx = find(all(p), x) - begin(p);
            moves.pb({idx, l});
            if(use[idx] && n > 2) {
                rep(i, 0, n){
                    if(!use[i] && i != l && (p[i] <= x) == tp[idx]) {
                        moves.pb({idx, i});
                        break;
                    }
                }
            }
        }
        cout << sz(moves) << "\n";
        for(auto [i, j] : moves) cout << i+1 << " " << j+1 << "\n";
    }    
    
    return 0;
}
