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
    while(true){
        int n, a, b; cin >> n >> a >> b;
        if(n == 0) break;
        using a3 = array<int, 3>;
        auto cmp = [](a3 a, a3 b)->bool{
            return a[1] - a[2] < b[1] - b[2];
        };
        deque<a3> order;
        rep(i, 0, n){
            a3 info; cin >> info[0] >> info[1] >> info[2];
            order.pb(info);
        }
        sort(all(order), cmp);
        int ans = 0;
        while(sz(order) && order.front()[1] <= order.front()[2]){
            int r = min(order.front()[0], a);
            order.front()[0] -= r;
            a -= r;
            ans += r * order.front()[1];
            // cout << "removing " << r << " from left" << nL;
            if(order.front()[0] == 0) order.pop_front();
            else break;
        }
        while(sz(order) && order.back()[1] >= order.back()[2]){
            int r = min(order.back()[0], b);
            order.back()[0] -= r;
            b -= r;
            ans += r * order.back()[2];
            // cout << "removing " << r << " from right" << nL;
            if(order.back()[0] == 0) order.pop_back();
            else break;
        }
        if(a){
            while(sz(order)){
                auto [k, da, db] = order.front();
                ans += k * da;
                order.pop_front();
            }
        }
        else{
            while(sz(order)){
                auto [k, da, db] = order.front();
                ans += k * db;
                order.pop_front();
            }
        }
        cout << ans << nL;
    }

    
    return 0;
}
