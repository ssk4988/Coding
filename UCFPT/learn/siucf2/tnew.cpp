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
        int n, t; cin >> n >> t;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        set<vi> in;
        set<vi> seen;
        rep(i, 0, t) {
            vi b(n);
            rep(j, 0, n) cin >> b[j];
            in.insert(b);
        }
        if(!in.count(a)){
            cout << "0\n";
            continue;
        }
        queue<pair<int, vi>> q;
        q.push({0, a});
        seen.insert(a);
        int ans = -1;
        while(sz(q)) {
            auto [d, u] = q.front(); q.pop();
            rep(i, 0, n) {
                u[i]++;
                if(!in.count(u)) {
                    ans = d+1;
                    goto done;
                }
                if(!seen.count(u)) {
                    seen.insert(u);
                    q.push({d+1, u});
                }
                u[i]--;
            }
        }
        done:
        cout << ans << "\n";
    }
    return 0;
}
