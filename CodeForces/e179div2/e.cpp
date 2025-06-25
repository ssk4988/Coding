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
        int n, q; cin >> n >> q;
        vi a(n);
        {
            string s; cin >> s;
            rep(i, 0, n) a[i] = s[i] - 'a';
        }
        vector dq(3, vector<set<int>>(3));
        rep(i, 0, q) {
            char x, y; cin >> x >> y;
            dq[x-'a'][y-'a'].insert(i);
        }
        rep(i, 0, n) {
            if(a[i] == 0) continue;
            if(a[i] == 1) {
                if(sz(dq[1][0])) {
                    dq[1][0].erase(begin(dq[1][0]));
                    a[i] = 0;
                    continue;
                }
                if()
            }
        }
    }
    
    return 0;
}
