#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int odd = 0;
    int base = 0;
    int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
    rep(i, 0, n) {
        int v; cin >> v; base += v/2;
        odd += v % 2;
    }
    int x = base + odd;
    int y = base;
    while(odd && (y < y1 || x > x2)) {
        x--;
        y++;
        odd--;
    }
    cout << ((x1 <= x && x <= x2 && y1 <= y && y <= y2) ? "Yes" : "No") << "\n";


    return 0;
}
