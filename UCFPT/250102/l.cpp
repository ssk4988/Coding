#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    ranges::sort(a);
    ranges::sort(b);

    int l = 0, r = 0;
    int saved = 0;

    while (l < n) {
        if (a[l]-1 > l+r) break;
        saved++;
        a[l]--;
        while (true) {
            if (l < n && a[l] <= l+r) l++;
            else if (r < m && b[r] <= l+r) r++;
            else break;
        }
    }
    cout << l << " " << saved << "\n";
    for (int i = l; i < n; i++) a[i]--;
    saved += n - l;

    // cout << l << " " << r << " " << saved << endl;

    while (r < m) {
        int need = max(0, b[r] - (l+r));
        // cout << l << " " << r << " " << saved << " " << need << endl;
        if (need > saved) {
            cout << "NO\n";
            return;
        }
        saved -= need;
        r++;
        while (true) {
            if (l < n && a[l] <= l+r) l++;
            else if (r < m && b[r] <= l+r) r++;
            else break;
        }
    }
    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t; while(t--)
    solve();

    return 0;
}
