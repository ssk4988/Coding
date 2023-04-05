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
        int q; cin >> q;
        ll l = 1; ll r = 1'000'000'000'000'000'000LL;
        auto findn = [&](ll a, ll b, ll target) -> ll{
            if(target <= a) return 1;
            return 1 + (target - a + (a - b - 1)) / (a - b);
        };
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 1){
                ll a, b, n; cin >> a >> b >> n;
                ll l1, r1 = a + (a - b) * (n - 1);
                if(n == 1){
                    l1 = 1;
                }
                else{
                    l1 = 1 + a + (a - b) * (n - 2);
                }
                ll newl = max(l1, l);
                ll newr = min(r1, r);
                if(newl <= newr){
                    l = newl;
                    r = newr;
                    cout << "1 ";
                }
                else{
                    cout << "0 ";
                }
            }
            else{
                ll a, b; cin >> a >> b;
                ll ln = findn(a, b, l), rn = findn(a, b, r);
                if(ln != rn){
                    cout << "-1 ";
                }
                else{
                    cout << ln << " ";
                }
            }
        }
        cout << nL;
    }
    
    return 0;
}
