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
    // int n; cin >> n;
    // vi a(n);
    // rep(i, 0, n)cin >> a[i];
    // vi res;
    // rep(i, 0, n){
    //     rep(j, i + 1, n){
    //         res.pb(a[i] + a[j]);
    //     }
    // }
    // sort(all(res));
    // for(int i : res) cout << i << " ";
    // cout << nL;
    int n; cin >> n;
    int n2 = n * (n - 1) / 2;
    vi a(n2);
    rep(i, 0, n2) cin >> a[i];
    sort(all(a));
    // a[0] - x0 = x1
    // a[1] - x0 = x2
    // brute force the sum of x1 and x2
    // x1 + x2 = a[0] + a[1] - 2 * x0
    rep(i, 2, n2){
        int s1 = a[0] + a[1] - a[i];
        if(s1 <= 0 || s1 % 2 != 0) continue;
        int x0 = s1 / 2, x1 = a[0] - x0, x2 = a[1] - x0;
        vi v = {x0, x1, x2};
        multiset<ll> ss(all(a));
        rep(i, 0, sz(v))
            rep(j, i + 1, sz(v))
                ss.erase(ss.find(v[i] + v[j]));
        bool works = true;
        while(sz(ss) && works){
            int x = *ss.begin() - v[0];
            for(int i : v){
                if(ss.find(i + x) == ss.end()){
                    works = false;
                    break;
                }
                ss.erase(ss.find(i + x));
            }
            v.pb(x);
        }
        if(works){
            for(int i : v) cout << i << " ";
            cout << "\n";
            break;
        }
    }
    return 0;
}
