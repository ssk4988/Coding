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
    int n, q; cin >> n >> q;
    priority_queue<string, vector<string>, greater<>> present;
    map<string, vi> idxs;
    int curbus = 0;
    rep(i, 0, n) {
        string t; cin >> t;
        if(t == "BUS") {
            int capacity; cin >> capacity;
            while(capacity && sz(present)) {
                string s = present.top();
                present.pop();
                idxs[s].pb(curbus);
                capacity--;
            }
            curbus++;
        } else {
            string s; cin >> s;
            present.push(s);
        }
    }
    rep(i, 0, q) {
        string s; int l, r; cin >> s >> l >> r; l--;
        cout << lower_bound(all(idxs[s]), r)-lower_bound(all(idxs[s]), l) << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
