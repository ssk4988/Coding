#include <bits/stdc++.h>
#include <bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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

#pragma GCC optimize("O3")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

ll hsh(const int a, const int b){
    return (ll(a) << 32) + b;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    srand(time(NULL));
    rep(cn, 0, nc){
        int a, b, c, d, m; 
        cin >> a >> b >> c >> d >> m;
        // a = abs(rand() * rand()), b = abs(rand() * rand()), c = abs(rand() * rand()), d = abs(rand() * rand()), m = abs(rand() * rand());
        // cout << a << " " << b << " " << c << " " << d << " " << m << nL;
        unordered_set<ll> inq;
        
        map<pi, int> seen;
        bool solved = false;
        queue<pair<pi, int>> q;
        q.push({{a, b}, 0});
        inq.emplace(hsh(a, b));
        int ans = -1;
        int cnt = 0;
        while(!q.empty()){
            auto [p, t] = q.front();
            q.pop();
            auto [x, y] = p;

            if(x == c && y == d){
                if(ans == -1){
                    ans = t;
                    cnt = 1;
                }
                else if(t == ans) cnt++;
                // ans = t;
                // break;
            }
            if(inq.count(hsh(x & y, y)) == 0){
                // if((x & y) == c && y == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x & y, y}, t+1});
                inq.emplace(hsh(x & y, y));
            }
            if(inq.count(hsh(x | y, y)) == 0){
                // if((x | y )== c && y == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x | y, y}, t+1});
                inq.emplace(hsh(x | y, y));
            }
            if(inq.count(hsh(x, y ^ x)) == 0){
                // if(x == c && (y ^ x) == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x, y ^ x}, t+1});
                inq.emplace(hsh(x, y ^ x));
            }
            if(inq.count(hsh(x, y ^ m)) == 0){
                // if(x == c && (y ^ m) == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x, y ^ m}, t+1});
                inq.emplace(hsh(x, y ^ m));
            }
        }
        if(ans != -1){
            cout << ans << " "<< cnt << " " << a << " " << b << " " << c << " "<< d << " " << m << nL;
        }
        // cout << ans << nL;
        // auto bt = [&](int x, int y, auto &&bt)->void{
        //     if(seen.count({x, y})) return;
        //     seen.insert({x, y});
        //     if(seen.count({c, d})){

        //     }
        //     bt(x & y, y, bt);
        //     bt(x | y, y, bt);
        //     bt(x, x ^ y, bt);
        //     bt(x, y ^ m, bt);
        // };
        // bt(a, b, bt);
        // cout << seen.size() << nL;
    }
    
    return 0;
}