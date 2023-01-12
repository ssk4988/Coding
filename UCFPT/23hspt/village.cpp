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
    int nc;
    cin >> nc;
    rep(cn, 0, nc){
        map<string, int> name;
        name["command"] = 0;
        int k = 1;
        int n, m; cin >> n >> m;
        vector<pi> inv(n);
        rep(i, 0, n){
            string na;
            cin >> inv[i].s >> na;
            if(name.find(na) == name.end()){
                name[na] = k++;
            }
            inv[i].f = name[na];
        }
        vector<pair<pi, pi>> trades(m);
        rep(i, 0, m){
            string na1, na2;
            cin >> trades[i].f.s >> na1 >> trades[i].s.s >> na2;
            if(name.find(na1) == name.end()){
                name[na1] = k++;
            }
            if(name.find(na2) == name.end()){
                name[na2] = k++;
            }
            trades[i].f.f = name[na1];
            trades[i].s.f = name[na2];
        }
        vi start(k);
        rep(i, 0, n){
            start[inv[i].f] += inv[i].s;
        }
        bool works = false;
        vi topsort;
        auto ts = [&](int cur) -> void{

        };
        auto dfs = [&](vi &state, int trade, auto &&dfs) -> void {

        };
    }
    
    return 0;
}