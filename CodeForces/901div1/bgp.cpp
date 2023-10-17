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

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

// ll hsh(int a, int b){}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};



#include <bits/extc++.h> /** keep-include */
// To use most bits rather than just the lowest ones:
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};

ll hsh(int a, int b){
    return ((a + 0LL) << 32) ^ b;
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    srand(time(NULL));
    rep(cn, 0, nc){
        int a, b, c, d, m; 
        // cin >> a >> b >> c >> d >> m;
        a = abs(rand() * rand()), b = abs(rand() * rand()), c = abs(rand() * rand()), d = abs(rand() * rand()), m = abs(rand() * rand());
        // cout << a << " " << b << " " << c << " " << d << " " << m << nL;
        // gp_hash_table<long long, int, custom_hash> inq;
        // unordered_set<pair<int, int>> inq;
        __gnu_pbds::gp_hash_table<ll,int,chash> inq({},{},{},{},{1<<16});
        // map<pi, int> seen;
        bool solved = false;
        queue<pair<pi, int>> q;
        q.push({{a, b}, 0});
        inq[hsh(a, b)] = 1;
        int ans = -1;
        while(!q.empty()){
            auto [p, t] = q.front();
            q.pop();
            auto [x, y] = p;

            if(x == c && y == d){
                ans = t;
                break;
            }
            if(inq[hsh(x & y, y)] == 0){
                // if((x & y) == c && y == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x & y, y}, t+1});
                inq[hsh(x & y, y)] = 1;
            }
            if(inq[hsh(x | y, y)] == 0){
                // if((x | y )== c && y == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x | y, y}, t+1});
                inq[hsh(x | y, y)] = 1;
            }
            if(inq[hsh(x, y ^ x)] == 0){
                // if(x == c && (y ^ x) == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x, y ^ x}, t+1});
                inq[hsh(x, y ^ x)] = 1;
            }
            if(inq[hsh(x, y ^ m)] == 0){
                // if(x == c && (y ^ m) == d){
                //     ans = t + 1;
                //     break;
                // }
                q.push({{x, y ^ m}, t+1});
                inq[hsh(x, y ^ m)] = 1;
            }
        }
        cout << ans << " " << inq.size() <<  nL;
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