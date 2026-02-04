#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const int N = 101;
const int H = 351;
const int W = 901;
bool seen[N][H][W][2];
int n, h, w; 
vi hs, ts, ord;
vi stacked, upright;

void dfs(int i, int wleft, int hleft, bool up) {
    if(wleft < 0 || hleft < 0) return;
    if(seen[i][wleft][hleft][up]) return;
    seen[i][wleft][hleft][up] = 1;
    if(i == n) {
        if(!up) return;
        cout << "upright ";
        for(int x : upright) {
            cout << x+1 << " ";
        }
        cout << "\n";
        cout << "stacked ";
        for(int x : stacked) {
            cout << x+1 << " ";
        }
        cout << "\n";
        exit(0);
    }
    int idx = ord[i];
    // upright
    if(wleft >= ts[idx] && hs[idx] <= h) {
        upright.push_back(idx);
        dfs(i+1, wleft-ts[idx], hleft, true);
        upright.pop_back();
    }
    // stacked
    if(hleft >= ts[idx]) {
        stacked.push_back(idx);
        dfs(i+1, wleft, hleft-ts[idx], up);
        stacked.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> h >> w;
    hs = vi(n);
    ts = vi(n);
    rep(i, 0, n) {
        cin >> hs[i] >> ts[i];
    }
    ord = vi(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) { return hs[i] > hs[j]; });
    int wleft = w;
    rep(i, 0, n) {
        int idx = ord[i];
        stacked.push_back(idx);
        if(hs[idx] <= wleft && ts[idx] <= h) {
            dfs(i+1, wleft-hs[idx], h-ts[idx], sz(upright) > 0);
        }
        stacked.pop_back();
        upright.push_back(idx);
        wleft -= ts[idx];
        if(hs[idx] > h) break;
    }
    cout << "impossible\n";
    return 0;
}
