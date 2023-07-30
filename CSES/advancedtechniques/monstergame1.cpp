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

ll eval(pl &line, ll x){
    return line.f * x + line.s;
}

struct cht {
    deque<pl> lines;
    ll query(ll x){
        while(lines.size() > 1 && eval(lines[0], x) > eval(lines[1], x)) lines.pop_front();
        return eval(lines[0], x);
    }
    void add(pl line){
        while(sz(lines) > 1){
            // if(lines.back().f == line.f){
            //     lines.pop_back();
            //     continue;
            // }
            if ((lines[sz(lines) - 1].s - lines[sz(lines) - 2].s) * (-line.f + lines[sz(lines) - 2].f) >= (line.s - lines[sz(lines) - 2].s) * (-lines[sz(lines) - 1].f + lines[sz(lines) - 2].f)){
                lines.pop_back();
            }
            else break;
        }
        lines.pb(line);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll x; cin >> n >> x;
    cht c;
    c.add({x, 0});
    vl s(n), f(n);
    rep(i, 0, n) cin >> s[i];
    rep(i, 0, n) cin >> f[i];
    rep(i, 0, n){
        ll t = c.query(s[i]);
        c.add({f[i], t});
    }
    cout << c.query(s.back()) << nL;

    
    return 0;
}