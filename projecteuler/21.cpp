#include <bits/stdc++.h>
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
    unordered_map<int, int> prop;
    auto calc = [&](int i)->int{
        if(prop[i] != 0) return prop[i];
        for(int j = 1; j < i && j * j <= i; j++){
            if(i % j == 0){
                prop[i] += j;
                if(i / j != i && i / j < i) prop[i] += i / j;
            }
        }
        return prop[i];
    };
    int ans = 0;
    rep(i, 1, 10000){
        if(calc(calc(i)) == i && calc(i) != i) ans += i;
    }
    cout << ans << nL;
    
    return 0;
}
