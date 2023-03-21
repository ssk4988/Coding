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
    int n; cin >> n;
    vvi v;
    rep(i, 0, n){
        int a, b; cin >> a >> b;
        v.pb({a,b,i});
    }
    sort(all(v));
    set<pi> ends;
    vi ans(n);
    rep(i, 0, n){
        if(ends.size() == 0 || (*ends.begin()).f >= v[i][0]){
            ends.insert({v[i][1], int(ends.size()) + 1});
            ans[v[i][2]] = ends.size();
        }
        else{
            pi v1 = *ends.begin();
            ans[v[i][2]] = v1.s;
            v1.f = v[i][1];
            ends.erase(ends.begin());
            ends.insert(v1);
        }
    }
    cout << ends.size() << nL;
    rep(i, 0, n){
        cout << ans[i] << " ";
    }
    cout << nL;
    
    return 0;
}
