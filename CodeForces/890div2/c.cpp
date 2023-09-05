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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; ll k; cin >> n >> k;
        vl cur;
        auto solve = [&]()->ll{
            // sort(all(cur));
            ll ans = cur.back();
            ll left = k;
            ll target = ans;
            for(int i = sz(cur) - 2; i >= 0 && left > 0 && cur[i] <= ans; i--){

                ll add = min(left, ans + 1 - cur[i]);
                ans = max(ans, cur[i] + add);
                left -= add;
            }
            return ans;
        };
        ll answer = 0;
        rep(i, 0, n){
            ll v; cin >> v;
            cur.pb(v);
        }
        while(sz(cur)){
            answer = max(answer, solve());
            cur.pop_back();
        }
        // rep(i, 0, n){
        //     ll v; cin >> v;
        //     if(sz(cur) == 0 || v >= cur.back()) cur.pb(v);
        //     else{
        //         answer = max(answer, solve());
        //         cur.pb(v);
        //     }
        // }
        // if(sz(cur)) answer = max(answer, solve());
        cout << answer << nL;
    }
    
    return 0;
}
