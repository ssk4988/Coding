#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int c; string s; cin >> c >> s;
        if(s == "1/1"){
            cout << c << " 1/2\n";
            continue;
        }
        int slash = s.find('/');
        ll num = stoll(s.substr(0, slash)), denom = stoll(s.substr(slash+1));
        vll dir;
        for(ll n = num, d = denom; n != 1 || d != 1; ){
            if(n > d) {
                dir.pb({1, (n - d + d - 1) / d});
                n -= d * dir.back().s;
            } else dir.pb({0, (d - n + n - 1) / n}), d -= n * dir.back().s;
        }
        if(sz(dir) == 1 && dir[0].f == 1){
            cout << c << " " << 1 << "/" << (2+dir[0].s) << "\n";
            continue;
        }
        reverse(all(dir));
        ll suff = 0;
        for(int i = sz(dir) - 1; i >= 0; i--) {
            if(dir[i].f == 0){
                while(sz(dir) > i+1) dir.pop_back();
                dir[i].s--;
                if(dir[i].s == 0) dir.pop_back();
                dir.push_back({1, 1});
                if(suff) dir.push_back({0, suff});
                break;
            }
            suff += dir[i].s;
        }
        num = 1, denom = 1;
        for(auto [d, t] : dir) {
            if(d) num += denom * t;
            else denom += num * t;
        }
        cout << c << " " << num << "/" << denom << "\n";
    }
    
    return 0;
}
