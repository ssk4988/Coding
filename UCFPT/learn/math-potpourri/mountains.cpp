#pragma GCC optimize("O2")
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

const int LIM = 35005;
bool composite[LIM];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    composite[0] = composite[1] = true;
    rep(i, 2, LIM){
        if(!composite[i] && ll(i) * i < LIM){
            for(int j = i * i; j < LIM; j+=i) composite[j] = true;
        }
    }
    vvi cands;
    cands.pb({0});
    rep(i, 1, LIM){
        rep(j, 0, sz(cands)){
            bool bad = false;
            for(int k = sz(cands[j]) - 1; k >= 0; k--){
                if(composite[i - cands[j][k]]){
                    bad = true;
                    break;
                }
            }
            if(!bad){
                vi c(cands[j]);
                c.pb(i);
                cands.pb(c);
            }
        }
    }
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vl cnt(n), prefcnt(n+1), prefidx(n+1);
        rep(i, 0, n){
            cin >> cnt[i];
            prefcnt[i+1] = cnt[i] + prefcnt[i];
            prefidx[i+1] = cnt[i] * i + prefidx[i];
        }
        ll best = LLONG_MAX;
        for(auto &v : cands){
            // if(v.back() > 2 * n + 1000) continue;
            rep(start, 0, n){
                if(start + v.back() >= n) break;
                ll ans = 0;
                // before start
                ans += start * prefcnt[start] - prefidx[start];
                // after end
                int endidx = start + v.back();
                ans += prefidx[n] - prefidx[endidx] - endidx * (prefcnt[n] - prefcnt[endidx]);
                // if(debug) cout << ans << "\n";
                if(ans >= best) continue;
                rep(i, 0, sz(v) - 1){
                    int l = start + v[i];
                    int r = start + v[i+1];
                    int md = l + (r - l + 1) / 2;
                    ans += prefidx[md] - prefidx[l] - l * (prefcnt[md] - prefcnt[l])
                    // if(debug) cout << ans <<"\n";
                    + r * (prefcnt[r] - prefcnt[md]) - (prefidx[r] - prefidx[md]);
                    // if(debug) cout << ans << "\n";
                }
                best = min(best, ans);
            }
        }
        cout << best << "\n";
    }
    
    return 0;
}
