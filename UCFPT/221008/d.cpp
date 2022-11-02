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
    vvi bars;
    map<int, vpi> h;
    int a[n];
    a[0] = 0;
    rep(i, 0, n - 1){
        a[i+1]=i+1;
        int k;
        bars.pb(vi());
        cin >> k;
        while(k != 0){
            bars[i].pb(k);
            h[k].pb(mp(i, bars[i].size()));
            cin >> k;
        }
    }
    for(auto &p : h){
        for(auto &k : p.s){
            swap(a[k.f], a[k.f+1]);
        }
    }
    vpi ans;
    for(auto iter = h.rbegin(); iter != h.rend(); iter++){
        for(auto &p : iter->s){
            int k = p.f;
            if(a[k] > a[k+1]){
                ans.pb(mp(k + 1, p.s));

                swap(a[k], a[k+1]);
            }
        }
    }
    cout << ans.size() << nL;
    for(auto &p : ans){
        cout << p.f << " " << p.s << nL;
    }
    
    
    return 0;
}