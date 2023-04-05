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
        int n;
        ll c, d;
        cin >> n >> c >> d;
        vi a;
        map<int, int> freq;
        rep(i, 0, n){
            int v; cin >> v;
            freq[v]++;
        }
        ll ans = 0;
        for(auto &p : freq){
            if(p.s > 1){
                ans += c * (p.s - 1);
            }
            a.pb(p.f);
        }
        ll bestrem = LLONG_MAX;
        bestrem = min(bestrem, (sz(a) - (a[0] == 1)) * c + d * (a[0] != 1));
        ll numexc = 0;
        rep(i, 0, sz(a)){
            if(i > 0) numexc += a[i] - a[i - 1] - 1;
            else numexc += a[i] - 0 - 1;
            bestrem = min(bestrem, (sz(a) - 1 - i) * c + d * numexc);
        }
        cout << (ans + bestrem) << nL;
    }
    
    return 0;
}
