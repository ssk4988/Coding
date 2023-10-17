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
    int nc; cin >> nc;
    srand(time(NULL));
    rep(cn, 0, nc){
        int a, b, c, d, m; 
        // cin >> a >> b >> c >> d >> m;
        a = abs(rand() * rand()), b = abs(rand() * rand()), c = abs(rand() * rand()), d = abs(rand() * rand()), m = abs(rand() * rand());
        // cout << a << " " << b << " " << c << " " << d << " " << m << nL;
        set<pair<int, int>> inq;
        map<pi, int> seen;
        bool solved = false;
        queue<pair<pi, int>> q;
        q.push({{a, b}, 0});
        inq.emplace(a, b);
        int ans = -1;
        while(!q.empty()){
            auto [p, t] = q.front();
            q.pop();
            auto [x, y] = p;

            if(x == c && y == d){
                ans = t;
                break;
            }
            if(inq.count({x & y, y}) == 0){
                if((x & y) == c && y == d){
                    ans = t + 1;
                    break;
                }
                q.push({{x & y, y}, t+1});
                inq.emplace(x & y, y);
            }
            if(inq.count({x | y, y}) == 0){
                if((x | y )== c && y == d){
                    ans = t + 1;
                    break;
                }
                q.push({{x | y, y}, t+1});
                inq.emplace(x | y, y);
            }
            if(inq.count({x, y ^ x}) == 0){
                if(x == c && (y ^ x) == d){
                    ans = t + 1;
                    break;
                }
                q.push({{x, y ^ x}, t+1});
                inq.emplace(x, y ^ x);
            }
            if(inq.count({x, y ^ m}) == 0){
                if(x == c && (y ^ m) == d){
                    ans = t + 1;
                    break;
                }
                q.push({{x, y ^ m}, t+1});
                inq.emplace(x, y ^ m);
            }
        }
        cout << ans << " " << sz(inq) << nL;
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