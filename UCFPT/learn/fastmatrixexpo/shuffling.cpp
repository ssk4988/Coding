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
        int n, p; cin >> n >> p;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
        }
        vi v(n);
        vvi cycles;
        rep(i, 0, n){
            if(v[i]) continue;
            int c = i;
            cycles.pb({});
            while(!v[c]){
                v[c] = true;
                cycles.back().pb(c);
                c = a[c];
            }
        }
        vi ans(n);
        for(auto c : cycles){
            rep(i, 0, sz(c)){
                ans[c[i]] = c[(i + p) % sz(c)];
            }
        }
        rep(i, 0, n){
            cout << (ans[i] + 1) << " ";
        }
        cout << nL;
    }
    
    return 0;
}
