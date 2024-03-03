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

using a2 = array<ll, 2>;

a2 operator+(a2 a, a2 b){
    return {a[0] + b[0], a[1] + b[1]};
}

a2 operator*(a2 a, ll k){
    return {a[0] * k, a[1] * k};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n; ll v; cin >> v;
    vector<a2> items(n); // worth, volume;
    vl left(n), used(n);
    rep(i, 0, n){
        cin >> left[i] >> items[i][0] >> items[i][1];
    }
    a2 cur = {0, 0}; // worth, volume
    auto &[curw, curv] = cur;
    rep(i, 0, n){
        ll add = min(left[i], (v - curv) / items[i][1]);
        left[i] -= add;
        used[i] += add;
        cur = cur + items[i] * add;
    }
    const ll WIDTH = 20 * 1000 * 1000 * 2 + 10;
    const ll MAX_ITEMS = 1000;
    const ll refidx = WIDTH / 2;
    const ll ref = curv;
    const ll BAD = -1e18;
    vl knapsack(WIDTH, BAD);
    knapsack[refidx] = curw;
    auto itemize = [](a2 item, ll cnt) -> vector<a2> {
        vector<a2> res;
        for(ll p = 1; cnt; cnt -= p, p = min(2 * p, cnt)){
            res.pb(item * p);
        }
        return res;
    }; 
    rep(i, 0, n){
        vector<a2> add = itemize(items[i], min(MAX_ITEMS, left[i]));
        vector<a2> sub = itemize(items[i], min(MAX_ITEMS, used[i]));
        rep(j, 0, sz(sub)){
            sub[j] = sub[j] * -1;
        }
        for(auto [iw, iv] : add){
            for(int j = WIDTH-1; j >= 0; j--){
                if(knapsack[j] == BAD || j + iv >= WIDTH || j + iv < 0){
                    continue;
                }
                knapsack[j + iv] = max(knapsack[j + iv], knapsack[j] + iw);
            }
        }
        for(auto [iw, iv] : sub){
            for(int j = 0; j < WIDTH; j++){
                if(knapsack[j] == BAD || j + iv >= WIDTH || j + iv < 0){
                    continue;
                }
                knapsack[j + iv] = max(knapsack[j + iv], knapsack[j] + iw);
            }
        }
    }
    ll ans = 0;
    rep(i, 0, WIDTH){
        if(knapsack[i] != BAD && i - refidx + ref <= v){
            ans = max(ans, knapsack[i]);
        }
    }
    cout << ans << "\n";
    
    return 0;
}