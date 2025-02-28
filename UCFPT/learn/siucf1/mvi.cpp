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
    vl mod = vl{ll(1e9+7), ll(1e9+9)};
    rep(cn, 0, nc) {
        vector<string> s(3);
        vector<vl> res(3);
        rep(i, 0, 3) {
            cin >> s[i];
            rep(j, 0, 2) {
                ll cur = 0;
                for(char c : s[i]) {
                    cur = (cur * 10 + c-'0') % mod[j];
                }
                res[i].pb(cur);
            }
        }
        bool works = true;
        rep(j, 0, 2) {
            if((res[0][j] * res[1][j]) % mod[j] != res[2][j]) works = false;
        }
        cout << (works ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
