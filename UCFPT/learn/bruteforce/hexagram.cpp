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
        vi v(12);
        rep(i, 0, 12){
            cin >> v[i];
        }
        if(v == vi(12)){
            break;
        }
        int ans = 0;
        vi path(12);
        auto go = [&](vi &used, int numused, int sum, auto &&go) -> void {
            if(numused == 4){
                sum = path[0] + path[1] + path[2] + path[3];
            }
            if(numused == 7 && sum != path[6] + path[5] + path[4] + path[3]){
                return;
            }
            if(numused == 9 && sum != path[6] + path[7] + path[8] + path[0]) return;
            if(numused == 11 && sum != path[9] + path[10] + path[2] + path[4]) return;
            if(numused == 12 && sum != path[9] + path[11] + path[1] + path[8]) return;
            if(numused == 12 && sum != path[10] + path[11] + path[5] + path[7]) return;
            if(numused == 12){
                // verify
                ans++;
                return;
            }
            rep(i, 0, 12){
                if(used[i]) continue;
                path[numused] = v[i];
                used[i] = true;
                go(used, numused + 1, sum, go);
                used[i] = false;
            }
        };
        vi used(12);
        go(used, 0, 0, go);
        ans /= 12;
        cout << ans << "\n";
    }
    
    return 0;
}
