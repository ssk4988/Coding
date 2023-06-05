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
    string s1, s2; cin >> s1 >> s2;
    set<string> se;
    map<string, int> m;
    rep(i, 1, sz(s1) + 1){
        rep(j, 0, sz(s2)){
            string ss1 = s1.substr(0, i) + s2.substr(j);
            se.insert(ss1);
            m[ss1]++;
        }
    }
    cout << sz(se) << nL;
    for(auto &p : m){
        if(p.s > 1) cout << p.f << " " << p.s << nL;
    }
    return 0;
}
