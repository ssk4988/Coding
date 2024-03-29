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
    rep(cn, 0, nc){
        int n; cin >> n;
        int queries = 0;
        auto qry = [&](int a, int b, int c, int d) -> int {
            queries++;
            assert(queries <= 3 * n);
            cout << "? " << a << " " << b << " " << c << " " << d << endl;
            char res; cin >> res;
            if(res == '<') return -1;
            if(res == '=') return 0;
            return 1;
        };
        auto greatestwith = [&](int x, vi &test) -> vi {
            assert(sz(test));
            vi best = {test[0]};
            rep(i, 1, sz(test)){
                int res = qry(x, best[0], x, test[i]);
                if(res == -1){
                    best = {test[i]};
                }
                else if(res == 0) best.pb(test[i]);
            }
            return best;
        };
        auto findsmallest = [&](vi &test) -> int {
            assert(sz(test));
            int best = test[0];
            rep(i, 1, sz(test)){
                int res = qry(best, best, test[i], test[i]);
                if(res == 1){
                    best = {test[i]};
                }
            }
            return best;
        };
        vi init;
        rep(i, 1, n) init.pb(i);
        vi test1 = greatestwith(0, init);
        assert(sz(test1));
        int large = test1[0];
        init.clear();
        rep(i, 0, n){
            if(i != large) init.pb(i);
        }
        test1 = greatestwith(large, init);
        int small = findsmallest(test1);
        cout << "! " << large << " "<< small << endl;
    }
    
    return 0;
}
