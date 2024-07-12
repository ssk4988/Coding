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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, x; cin >> n >> x;
        vi mp(x+1, -1);
        vi divs;
        rep(i, 1, x+1){
            if(x % i == 0){
                mp[i] = sz(divs);
                divs.pb(i);
            }
        }
        vi can(sz(divs));
        can[0] = 1;
        auto add = [&](ll v) -> void {
            for(int i = sz(can) - 1; i >= 0; i--) {
                ll p = divs[i] * v;
                if(p <= x && mp[p] != -1){
                    can[mp[p]] = can[mp[p]] | can[i];
                }
            }
        };
        int ans = 1;
        rep(i, 0, n){
            int v; cin >> v;
            add(v);
            if(can[mp[x]]) {
                ans++;
                can = vi(sz(divs));
                can[0] = 1;
                add(v);
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
