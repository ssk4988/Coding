#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n), b(n);
        rep(i, 0, n) {
            cin >> a[i]; a[i]--;
        }
        rep(i, 0, n) {
            cin >> b[i]; b[i]--;
        }
        bool works = true;
        vii sw;
        for(int t = n-1; t >= 0; t--) {
            int cur = find(all(a), t)-begin(a);
            int tar = find(all(b), t)-begin(b);
            if(tar < cur) {
                works = false;
                break;
            }
            if(tar == cur) continue;
            vi st;
            st.push_back(cur);
            rep(i, cur+1, tar+1) {
                if(a[i] > a[cur]) continue;
                while(a[st.back()] < a[i]) st.pop_back();
                st.push_back(i);
            }
            rep(i, 1, sz(st)) {
                sw.push_back({st[i-1], st[i]});
                swap(a[st[i-1]], a[st[i]]);
            }
        }
        if(works) {
            cout << sz(sw) << "\n";
            for(auto [u, v] : sw) {
                cout << u+1 << " " << v+1 << "\n";
            }
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
