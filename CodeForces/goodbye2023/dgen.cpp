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
    map<string, vi> mm;
    rep(i, 1, sqrt(1000000000)){
        int i2 = i * i;
        string s = to_string(i2);
        sort(all(s));
        mm[s].pb(i);
    }
    for(auto [s, v] : mm){
        if(sz(s) <= sz(v) && sz(s) <= 7){
            cout << s << " " << sz(v) << nL;
            // for(int i : v){
            //     cout << i << " " << (i * i) << nL;
            // }
        }
    }
    
    return 0;
}
