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
    string str; cin >> str;
    assert(sz(str) % 2 == 0);
    map<string, int> m;
    m["<<"] = 1;
    m[">>"] = -1;
    vi a;
    for(int i = 0; i < sz(str); i += 2){
        assert(m.count(str.substr(i, 2)));
        a.pb(m[str.substr(i, 2)]);
    }
    const int maxn = 130;
    const pi UNCALC = {-1, -1};
    vector<vpi> dp(maxn, vpi(maxn, UNCALC));
    rep(i, 1, maxn) dp[i][i - 1] = {true, -1};
    auto solve = [&](int l, int r, auto &&solve)->int {
        if(dp[l][r] != UNCALC) return dp[l][r].f;
        dp[l][r].f = false;
        if(l >= r) return dp[l][r].f;
        for(int k = l + 1; k < r; k += 2) {
            if(solve(l, k, solve) && solve(k + 1, r, solve)){
                dp[l][r] = {true, k};
            }
        }
        if(a[l] + a[r] == 0 && solve(l + 1, r - 1, solve)) {
            dp[l][r] = {true, r};
        }
        return dp[l][r].f;
    };

    if(solve(0, sz(a) - 1, solve)){
        auto bb = [&](int l, int r, auto &&bb)->void {
            if(l > r) return;
            if(dp[l][r].s == r){
                cout << '[';
                bb(l + 1, r - 1, bb);
                cout << ']';
            }
            else{
                bb(l, dp[l][r].s, bb);
                bb(dp[l][r].s + 1, r, bb);
            }
        };
        bb(0, sz(a) - 1, bb);
        cout << nL;
    }
    else{
        cout << "Keine Loesung\n";
    }
    
    
    return 0;
}