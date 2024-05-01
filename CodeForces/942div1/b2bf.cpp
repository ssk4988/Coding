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
    int LIM = 100;
    map<int, vpi> m, m1;
    set<pi> s;
    rep(a, 1, LIM){
        rep(b, 1, LIM){
            int g = __gcd(a, b);
            if((b * g) % (a + b) == 0){
                m[g].pb({a, b});
                s.insert({a, b});
                if(a <= b) m1[a].pb({g, b});
            }
        }
    }
    // for(auto [key, val] : m){
    //     if(key % 2 == 0 && sz(val) == 1) continue;
    //     cout << key << ": " << sz(val) << " pairs \n";
    //     for(auto [a, b] : val) cout << a << "," << b << "\n";
    // }
    int ans = 0;
    for(auto [a, val] : m){
        ans += sz(val);
    //     if(a % 2 == 0 && sz(val) == 1) continue;
    //     cout << a << ": " << sz(val) << " pairs \n";
    //     for(auto [g, b] : val) cout << b << "," << g << "\n";
    }
    cout << ans << "\n";
    // for(auto [a,b] : s){
    //     cout << a << "," << b << "\n";
    // }


    return 0;
}
