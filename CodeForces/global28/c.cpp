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

void solve() {
    string s; cin >> s;
    int n = sz(s);
    vi starts;
    int zind = -1;
    rep(i, 0, n){
        if(s[i] == '0') {
            zind = i;
            break;
        }
    }
    if(zind == -1){
        cout << 1 << " " << n << " " << 1 << " " << 1 << "\n";
        return;
    }
    rep(i, 0, zind){
        starts.pb(i);
    }
    rep(len, 1, n) {
        if(sz(starts) == 0) break;
        if(zind + len - 1 >= n) break;
        vi start2;
        bool fnd = false;
        for(int i : starts) {
            if(s[i + len - 1] != s[zind + len - 1]) {
                fnd = true;
                start2.pb(i);
            }
        }
        if(fnd) swap(starts, start2);
    }
    assert(sz(starts) > 0);
    cout << 1 << " " << n << " " << starts[0]+1 << " " << (starts[0] + 1 + n - zind - 1) << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
