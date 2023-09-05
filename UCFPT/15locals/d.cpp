#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll d, x, s; cin >> d >> x >> s;
        ll minlemon = INT_MAX, minsugar = INT_MAX;
        ll cursugar = 0;
        ll cost = 0;
        rep(i, 0, d){
            ll c, pl, ps; cin >> c >> pl >> ps;
            minlemon = min(minlemon, pl);
            minsugar = min(minsugar, ps);
            cost += minlemon * x * c;
            ll sugtobuy = cursugar >= c * s ? 0 : (c * s - cursugar + 80 - 1) / 80;
            cursugar += 80 * sugtobuy;
            cost += sugtobuy * minsugar;
            cursugar -= c * s;
        }
        cout << cost << "\n";
    }
}
