#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

void solve() {
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    map<int, ll> ans;
    vi test;
    rep(i, 1, 10){
        for(int j : {1, 3, 9}){
            test.push_back(i * j);
        }
    }
    vi gs(1 << 10);
    rep(mask, 0, sz(gs)){
        if(__builtin_popcount(mask) < 2) continue;
        vi c;
        rep(i, 0, 10){
            if((mask >> i) & 1) {
                c.push_back(i);
            }
        }
        gs[mask] = c[1] - c[0];
        rep(i, 2, sz(c)){
            gs[mask] = __gcd(gs[mask], c[i] - c[i-1]);
        }
        // if(mask < 50) cout << mask << " " << gs[mask] << "\n";
    }
    for(int target : test){
        if(ans.count(target)) continue;
        if(target < 10) {
            ans[target] = target;
            continue;
        }
        // cout << target << ":" << endl;
        for(ll cur = target; true; cur += target) {
            if(cur > 1e10) break;
            int mask = 0;
            for(ll c = cur; c; c /= 10) {
                mask |= 1 << (c % 10);
            }
            if(__builtin_popcount(mask) < 2) continue;
            ll g = __gcd(cur, 9LL * gs[mask]);
            // if(cur == 48) cout << cur << " " << g << endl;
            if(g == target) {
                ans[target] = cur;
                break;
            }
        }
        cout << target << ", " << ans[target] << endl;
    }

    // int t; cin >> t; while(t--)
    // solve();

    return 0;
}
