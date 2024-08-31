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
using vpi = vector<pi>;
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

const ll LIM = 1e18 + 1e9;

ll mult(ll a, ll b) {
    return min(a * b, LIM);
}
ll add(ll a, ll b) { return min(a + b, LIM); }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; ll k; cin >> n >> m >> k;
    vector dp(n+1, vector(n+1, vector(n+1, vector(n+1, -1))));
    auto go = [&](int pref, int fixedpoints, int balls, int boxes, auto &&go) -> ll {
        auto &ans = dp[pref][fixedpoints][balls][boxes];
        if(ans != -1) return ans;
        if (fixedpoints > m) return ans = 0;
        if (pref == n) {
            return fixedpoints == m && balls == 0 && boxes == 0;
        }
        ans = 0;
        // fixed point
        ans = add(ans, go(pref+1, fixedpoints+1, balls, boxes, go));
        // use ball, don't use box
        ans = add(ans, mult(boxes, go(pref+1, fixedpoints, balls+1, boxes-1, go)));
        for (auto useball : {0, 1}) {
            for(auto usebox : {0, 1}) {
                if(useball && boxes == 0) continue;
                if(usebox && balls == 0) continue;
                ans = add(ans, mult((usebox ? balls : 1) * (useball ? boxes : 1), go(pref+1, fixedpoints, balls + (usebox ? -1 : 1), boxes + (useball ? -1 : 1), go)));
            }
        }
        return ans;
    };
    int fixedpoints = 0;
    set<int> balls, boxes;
    ll cnt = go(0, 0, 0, 0, go);
    vi perm;
    if(cnt < k) {
        cout << "-1\n";
        return 0;
    }
    vi used(n);
    rep(pref, 0, n){
        rep(nxt, 0, n){
            if(used[nxt]) continue;
            if(nxt == pref){
                ll amt = go(pref+1, fixedpoints+1, sz(balls), sz(boxes), go);
                if (amt > k){
                    amt -= k;
                } else {
                    used[nxt] = true;
                    perm.push_back(nxt);
                    break;
                }
            }
            if(nxt < pref && balls.count(nxt)) {
                ll amt = go(pref+1, fixedpoints, sz(balls)-1, , go);
            }
        }
    }
    
    
    return 0;
}
