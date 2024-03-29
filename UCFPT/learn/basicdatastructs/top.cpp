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
    map<string, int> m;
    rep(i, 0, n){
        string str; cin >> str;
        m[str] = i;
    }
    vi perm(n);
    rep(i, 0, n){
        string str; cin >> str;
        perm[i] = m[str];
        // cout << i << " " << perm[i] << nL;
    }
    int pnt = 0;
    while(pnt < n){
        int mn = min(pnt, perm[pnt]), mx = max(pnt, perm[pnt]);
        pnt++;
        int s = 1;
        while(mx - mn + 1 > s){
            mn = min({mn, pnt, perm[pnt]}), mx = max({mx, pnt, perm[pnt]});
            pnt++;
            s++;
        }
        cout << s << nL;
    }
    
    return 0;
}
