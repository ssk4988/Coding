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
        int n, x; cin >> n >> x;
        x--;
        string s; cin >> s;
        int spaceleft = x, spaceright = n-1-x;
        int trueleft = 0;
        rep(i, 0, x) if(s[i] == '#') trueleft = i+1;
        int trueright = 0;
        rep(i, x+1, n) {
            if(s[i] == '#') {
                trueright = n-i;
                break;
            }
        }
        cout << 1+max(min(spaceleft, trueright), min(spaceright, trueleft)) << "\n";
    }
    
    return 0;
}
