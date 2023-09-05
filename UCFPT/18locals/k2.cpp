#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;
using pl = pair<ll, ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second
ll w, h, x;
// h < w
pl test(ll c){
    ll cur = 0, cnt = 0;
    vector<pl> ps;
    ps.pb({0, 0});

    // O(sqrt(c))
    for(ll i = 1; i * i <= c; i++){
        ll j = c / i;
        ps.pb({i, j});
        // ll rows = 
    }
    for(int i = sz(ps) - 1 - (ps.back().f * ps.back().f == c); i > 0; i--){
        auto [i1, j] = ps[i];
        ps.pb({j, i1});
    }
    ll lastrem = 0;
    while(sz(ps) && ps.back().f > h){
        lastrem = ps.back().s;
        ps.pop_back();
    }
    if(sz(ps) && ps.back().f < h){
        ps.pb({h, lastrem});
    }
    for(auto [i, j] : ps){
        cout << i << " " << j << "\n";
    }
    rep(i, 1, sz(ps)){
        auto [r, c] = ps[i];
        auto [r1, c1] = ps[i - 1];
        c = min(c, w);
        ll add = (r + r1 + 1) * (r - r1) / 2 * (c + 1) * c / 2;
        cur += add;
        cnt += c * (r - r1);
        if(cur > x){
            cur = x + 1;
            break;
        }
    }
    return {cur, cnt};
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // cin >> w >> h >> x;
    w = 233, h = 1000, x = 1000;
    // try all small cases
    if(w < h) swap(w, h);
    // ll lo = 
    pl res = test(10000);



    // ll lo = 1, hi = 10'000'000'000LL;
    // // rep(i, 1, 10){
    // //     res = test(i);
    // //     cout << i << " " << res.f << " " << res.s << "\n";

    // // }
    // while(lo < hi){
    //     ll mid = lo + (hi - lo + 1) / 2;
    //     pl res = test(mid);
    //     if(res.f <= x){
    //         lo = mid;
    //     } else hi = mid - 1;
    // }
    // pl res = test(lo);
    // ll rem = x - res.f;
    // res.s += (rem / (lo + 1));
    // cout << res.s << "\n";
    // res = test(10'000'000'000LL);
    // cout << res.f << " " << res.s << "\n";
    // test(4);
}
