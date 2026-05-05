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

int c;
int p[2000];
// x must be less than y
int dist(int x, int y) {
    if(p[x] < p[y]) swap(x, y);
    return min(p[x]-p[y], c+p[y]-p[x]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n >> c;
    rep(i, 0, n) cin >> p[i];
    rep(i, n, 2*n) p[i] = p[i-n];

    vi res(n/2);
    rep(s, 0, n) rep(e, s+1, n) {
        int d = min(p[e]-p[s], c + p[s] - p[e]);
        int l = s+1, r = e+1;
        int cnt = 0;
        while(true) {
            if(l == e || r == n+s) break;
            if(dist(l, r) >= d) {
                cnt++;
                l++, r++;
                continue;
            }

            int left = p[r]-p[l];
            int right = p[l]-p[r];
            if(left < 0) left += c;
            else right += c;

            if(left < right)
                r++;
            else
                l++;
        }
        res[cnt] = max(res[cnt], d);
    }

    for(int i = sz(res)-2; i >= 0; i--)
        res[i] = max(res[i], res[i+1]);

    for(int i = 0; i < sz(res); i++)
        cout << res[i] << ' ';
    cout << '\n';

    return 0;
}
