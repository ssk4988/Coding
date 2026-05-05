#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, c;
    cin >> n >> c;

    vector<int> f(c);
    for (int i = 0; i < c; i++) cin >> f[i];

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    vector<vector<int>> arr(c);
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;

        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            arr[x-1].push_back(i);
        }
    }

    for (int i = 0; i < c; i++) ranges::reverse(arr[i]);

    vector<int> rev(n+1, c);
    ll tot = 0;
    for (int i = 0; i < c; i++) {
        while (!arr[i].empty() && f[i] > 0) {
            int x = arr[i].back(); arr[i].pop_back();
            if (rev[x] == c) {
                rev[x] = i;
                f[i]--;
                tot += x;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << tot << "\n";
        int u = p[i];
        int v = rev[u];
        if (rev[u] < c) tot -= u;
        rev[u] = -1;
        while (v < c) {
            if (arr[v].empty()) break;
            int x = arr[v].back(); arr[v].pop_back();
            if (rev[x] < v) continue;
            swap(v, rev[x]);
            u = x;
        }
        if (u != p[i] && v == c) tot += u;
    }

    return 0;
}
