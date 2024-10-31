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
    ll n; cin >> n;
    vector dp(20, vector(10, vpl(10, {-1, -1})));
    auto go = [&](int place, int mx, int len, auto &&go) -> pl {
        if(place == -1){
            if(len == 0 && mx == 0) {
                return {1, 0};
            }
            if (len >= mx) return {1, 1};
            else return {0, len+1};
        }
        auto &[add, last] = dp[place][mx][len];
        if(add != -1) return pl{add, last};
        add = 0;
        last = len;
        rep(d, 0, 10){
            int nmx = max(mx, d);
            auto [add1, last1] = go(place-1, nmx, last, go);
            add += add1;
            last = last1;
        }
        // cout << "go " << place << " " << mx << " " << len << " = " << add <<"," << last << endl;
        return pl{add, last};
    };
    auto make = [&](ll u, auto &&go) -> ll {
        u++;
        ll add = 0, last = 0;
        vi digs;
        ll u1 = u;
        while(u1){
            digs.pb(u1 % 10);
            u1 /= 10;
        }
        int mx = 0;
        for(int p = sz(digs) - 1; p >= 0; p--){
            rep(i, 0, digs[p]){
                auto [add1, last1] = go(p-1, max(mx, i), last, go);
                // cout << "go " << p-1 << " " << max(mx, i) << " " << last << " = " << add1 << "," << last1 << endl;
                add += add1;
                last = last1;
            }
            mx = max(mx, digs[p]);
        }
        return add;
    };
    cout << make(n, go) << "\n";
    
    return 0;
}
