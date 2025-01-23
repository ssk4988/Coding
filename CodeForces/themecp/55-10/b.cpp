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
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    vl pref(sz(a)+1);
    partial_sum(all(a), begin(pref)+1);
    vl prefx(sz(a) + 1);
    rep(i, 0, n) prefx[i+1] = prefx[i] ^ a[i];
    vvi idxs(30);
    rep(i, 0, n) {
        rep(j, 0, 30) {
            if((a[i] >> j) & 1) {
                idxs[j].pb(i);
            }
        }
    }
    rep(_, 0, q) {
        int l, r; cin >> l >> r; l--;
        set<int> consider;
        rep(b, 0, 30) {
            int idx1 = lower_bound(all(idxs[b]), l) - begin(idxs[b]), idx2 = lower_bound(all(idxs[b]), r) - begin(idxs[b]);
            if(idx1 < sz(idxs[b]) && idxs[b][idx1] < r){ 
                consider.insert(idxs[b][idx1]);
            }
            idx1++;
            if(idx1 < sz(idxs[b]) && idxs[b][idx1] < r){ 
                consider.insert(idxs[b][idx1]);
            }
            if(idx2 > 0 && idxs[b][idx2-1] >= l) {
                consider.insert(idxs[b][idx2-1]);
            }
            idx2--;
            if(idx2 > 0 && idxs[b][idx2-1] >= l) {
                consider.insert(idxs[b][idx2-1]);
            }
        }
        vi v(all(consider));
        array<ll, 4> best{0, -1, l, l};
        for(int i : v) {
            for(int j : v) {
                int v1 = min(i, j), v2 = max(i, j);
                best = max(best, array<ll, 4>{pref[v2+1] - pref[v1] - (prefx[v2+1]^prefx[v1]), -(v2+1-v1), v1, v2});
            }
        }
        cout << best[2]+1 << " " << best[3]+1 << "\n";
    }    
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc; 
    rep(cn, 0, nc) {
        solve();
    }
    return 0;
}
