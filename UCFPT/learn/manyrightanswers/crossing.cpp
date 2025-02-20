#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"
using a3 = array<int, 3>;
void solve() {
    int n, r; cin >> n >> r;
    int allmask = (1 << n)-1;
    vector<a3> p(r);
    rep(i, 0, r) {
        rep(j, 0, 3) cin >> p[i][j], p[i][j]--;
    }
    vi valid(1 << n, 1);
    rep(i, 0, r) {
        rep(mask, 0, 1 << n) {
            vi b;
            rep(j, 0, 3) {
                b.pb((mask >> p[i][j])&1);
            }
            if(b[0] == b[1] && b[0] != b[2]) valid[mask] = false;
        }
    }
    const int inf = 1e9;
    vector<vii> dp(1 << n, vii(2, {inf, -1}));
    queue<array<int, 4>> q;
    q.push({0, 0, 0, -1});
    // mask represents what is on side 1
    while(sz(q)) {
        auto [d, mask, side, prv] = q.front(); q.pop();
        if(dp[mask][side].f != inf) continue;
        dp[mask][side] = {d, prv};
        int has = (side ? mask : allmask ^ mask);
        rep(i, 0, n) {
            rep(j, -1, i) {
                int sub = (1 << i);
                if(j > -1) sub ^= (1 << j);
                if((sub & has) != sub) continue;
                int nxt = mask ^ sub;
                if(!valid[nxt]) continue;
                q.push({d+1, nxt, side^1, mask});
            }
        }
    }
    int side = 1;
    int mask = allmask;
    vector<int> ans;
    while(mask != 0) {
        auto [d, prv] = dp[mask][side];
        ans.pb(mask ^ prv);
        side ^= 1;
        mask = prv;
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    for(int mask : ans){
        cout << __builtin_popcount(mask) << " ";
        rep(i, 0, n) if((mask >> i) & 1) cout << i+1 << " ";
        cout << "\n";
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
