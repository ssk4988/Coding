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
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vvi q(n);
        vi a(n);
        vi inq(n);
        set<pi> s;
        rep(i, 0, n)
        {
            cin >> a[i];
            s.insert({i, a[i]});
        }
        auto check = [&](int idx) -> void {
            if(inq[idx]) return;
            auto p = s.find({idx, a[idx]});
            if(p == s.end()) return;
            auto it = next(p);
            if (it != s.end() && it->s == a[idx] - 1)
            {
                q[a[idx]].pb(idx);
                inq[idx] = true;
            }
            if(!inq[idx] && it != s.begin()){
                it = prev(p);
                if (it->s == a[idx] - 1)
                {
                    q[a[idx]].pb(idx);
                    inq[idx] = true;
                }
            }
        };
        int mx = 0;
        rep(i, 0, n) mx = max(mx, a[i]);
        rep(i, 0, n){
            if(a[i] == mx)
                check(i);
        }
        bool valid = true;
        for(int x = n - 1; valid && x >= 0; x--){
            while(!q[x].empty()){
                int idx = q[x].back(); q[x].pop_back(); 
                if(!inq[idx]){
                    valid = false;
                    break;
                }
                inq[idx] = false;
                auto it = s.find({idx, a[idx]});
                auto nit = next(it);
                if(nit != s.end() && nit->s == x - 1){
                    int idx1 = nit->f;
                    s.erase({idx, a[idx]});
                    s.erase({idx1, a[idx1]});
                    a[idx] = x - 1;
                    s.insert({idx, a[idx]});
                    check(idx);
                    it = s.find({idx, a[idx]});
                }
                else if(it != s.begin() && (--it)->s == x - 1){
                    int idx1 = it->f;
                    s.erase({idx1, a[idx1]});
                    s.erase({idx, a[idx]});
                    a[idx1] = x - 1;
                    s.insert({idx1, a[idx1]});
                    check(idx1);
                    it = s.find({idx1, a[idx1]});
                }
                else{
                    valid = false;
                    break;
                }
                if(it != s.begin()){
                    check(prev(it)->f);
                }
                it = next(it);
                if(it != s.end()){
                    check(it->f);
                }
            }
        }
        if(sz(s) != 1 || (s.begin())->s != 0){
            valid = false;
        }
        cout << (valid ? "YES" : "NO") << nL;
    }

    return 0;
}
