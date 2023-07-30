#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using pl = pair<ll, ll>;
#define f first
#define s second
int main() {
    freopen("zanzibar.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int d = 1;
    rep(i, 2, 14){
        d = (d * i) / __gcd(d, i);
    }
    vi dp(2 * d + 1);
    dp[0] = true;
    rep(i, 0, sz(dp)){
        if(!dp[i]) continue;
        rep(j, 2, 14){
            int add = d / j;
            if(add + i < sz(dp)) dp[add + i] = true;
        }
    }
    vector<ll> valid;
    rep(i, 0, sz(dp)) if(dp[i]) valid.push_back(i);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll x, y; cin >> x >> y;
        pl t(x, y);
        pair<pl, pl> best = {{1, 1}, {-1, -1}};
        int lo = 0, hi = sz(valid);
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            ll a = valid[mid];
            if(a * y >= x * d) hi = mid;
            else lo = mid + 1;
        }
        {
            pl c(valid[lo], d);
            ll g = __gcd(c.f, c.s);
            c.f /= g;
            c.s /= g;
            pl fcopy(c), tcopy(t);
            fcopy.f *= t.s, fcopy.s *= t.s;
            tcopy.f *= c.s, tcopy.s *= c.s;
            pl res(abs(tcopy.f - fcopy.f), fcopy.s);
            g = __gcd(res.f, res.s);
            res.f /= g;
            res.s /= g;
            if(res.f * best.f.s < best.f.f * res.s){
                best = {res, c};
            }
        }
        if(lo > 0){
            pl c(valid[lo - 1], d);
            ll g = __gcd(c.f, c.s);
            c.f /= g;
            c.s /= g;
            pl fcopy(c), tcopy(t);
            fcopy.f *= t.s, fcopy.s *= t.s;
            tcopy.f *= c.s, tcopy.s *= c.s;
            pl res(abs(tcopy.f - fcopy.f), fcopy.s);
            g = __gcd(res.f, res.s);
            res.f /= g;
            res.s /= g;
            if(res.f * best.f.s < best.f.f * res.s){
                best = {res, c};
            }
        }
        // allow 0 to be paid???
        // rep(i, 0, sz(dp)){
        //     if(!dp[i]) continue;
        //     pl c(i, d);
        //     ll g = __gcd(c.f, c.s);
        //     c.f /= g;
        //     c.s /= g;
        //     pl fcopy(c), tcopy(t);
        //     fcopy.f *= t.s, fcopy.s *= t.s;
        //     tcopy.f *= c.s, tcopy.s *= c.s;
        //     pl res(abs(tcopy.f - fcopy.f), fcopy.s);
        //     g = __gcd(res.f, res.s);
        //     res.f /= g;
        //     res.s /= g;
        //     if(res.f * best.f.s < best.f.f * res.s){
        //         best = {res, c};
        //     }
        // }
        // rep(b, 2, 14){
        //     rep(a, 1, b){
        //         pl c(a, b);
        //         pl fcopy(c), tcopy(t);
        //         fcopy.f *= t.s, fcopy.s *= t.s;
        //         tcopy.f *= c.s, tcopy.s *= c.s;
        //         pl res(abs(tcopy.f - fcopy.f), fcopy.s);
        //         ll g = __gcd(res.f, res.s);
        //         res.f /= g;
        //         res.s /= g;
        //         if(res.f * best.f.s < best.f.f * res.s){
        //             best = {res, {a, b}};
        //         }
        //     }
        // }
        cout << "Case " << (cn + 1) << ": " << best.f.f << "/" << best.f.s << "\n"; // " " << best.s.f << "/" << best.s.s << "\n";
    }
}
