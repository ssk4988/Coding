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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    set<int> rem;
    rep(i, 0, n) rem.insert(i);
    rep(i, 0, n) {
        cin >> a[i];
        a[i]--;
        if(a[i] >= 0) rem.erase(a[i]);
    }
    const int inf = 1e9;
    a.insert(a.begin(), inf);
    a.pb(inf);
    rep(i, 1, n + 1){
        if(sz(rem) <= 4) break;
        if(a[i] == -2){
            for(int j : rem){
                if(abs(a[i - 1] - j) != 1 && abs(a[i + 1] - j) != 1){
                    a[i] = j;
                    break;
                }
            }
            rem.erase(a[i]);
        }
    }
    int left = sz(rem);
    vi v, x;
    for(int i : rem) v.pb(i);
    rep(i, 0, sz(a)){
        if(a[i] == -2){
            x.pb(i);
        }
    }
    if(left == 0){
        rep(i, 1, n + 1){
            cout << (a[i] + 1) << " ";
        }
        cout << "\n";
        return 0;
    }
    vvi dp(1 << left, vi(left, -1));
    vvi opt(1 << left, vi(left, -1));
    auto solve = [&](int mask, int lastidx, auto &&solve) -> int {
        int &res = dp[mask][lastidx];
        if(res != -1) return res;
        int filled = __builtin_popcount(mask);
        if(filled == left) return res = 1;
        res = 0;
        for(int i = 0; i < left; i++){
            if((mask >> i) & 1) continue;
            if(filled > 0 && abs(x[filled - 1] - x[filled]) == 1 && abs(v[lastidx] - v[i]) == 1) continue;
            if(abs(a[x[filled] - 1] - v[i]) == 1 || abs(a[x[filled] + 1] - v[i]) == 1) continue;
            if(solve(mask ^ (1 << i), i, solve) == 1){
                res = 1;
                opt[mask][lastidx] = i;
                return res;
            }
        }
        return res;
    };
    if(solve(0, 0, solve) == 0){
        cout << "-1\n";
        return 0;
    }
    int mask = 0, lastidx = 0;
    rep(i, 0, left){
        a[x[i]] = v[opt[mask][lastidx]];
        int o = opt[mask][lastidx];
        mask ^= 1 << o;
        lastidx = o;
    }
    rep(i, 1, n + 1){
        cout << (a[i] + 1) << " ";
    }    
    cout << "\n";
    return 0;
}