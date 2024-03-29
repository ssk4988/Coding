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
    int n; cin >> n;
    if(n <= 4){
        vi ans = {0, 1, 1, 0, 1};
        cout << ans[n] << "\n";
        return 0;
    }
    int left = n;
    int b = 1;
    int levels = 0;
    for(; left >= b; b *= 2){
        left -= b;
        levels++;
    }
    auto dfs = [&](int depth, bool right, auto &&dfs) -> int {
        int subsz = 1;
        if(depth == levels){
            if(right) subsz++;
            return subsz;
        }
        int leftsub = dfs(depth+1, false, dfs);
        int rightsub = dfs(depth + 1, true, dfs);
        if(right && leftsub % 2 == 0){
            leftsub++;
        }
        subsz += leftsub + rightsub;
        return subsz;
    };
    int used = dfs(1, false, dfs);
    if(n == used || n == used + 1){
        cout << 1 << "\n";
    }
    else{
        cout << 0 << "\n";
    }
    
    return 0;
}
