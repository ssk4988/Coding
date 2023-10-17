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
    vector<pair<ld, int>> a(n);
    rep(i, 0, n){
        cin >> a[i].f;
        a[i].s = i;
    }
    ld s; cin >> s;
    sort(all(a));
    reverse(all(a));
    ld lo = 0, hi = 5000 * 5000 + 100;
    vd v(n);
    rep(iter, 0, 200){
        ld mid = (lo + hi) / 2;
        v[0] = mid;
        rep(i, 1, n){
            if(mid <= a[i].f / 2){
                v[i] = v[0];
            }
            else if(mid <= a[0].f - a[i].f / 2){
                v[i] = a[i].f / 2;
            }
            else{
                v[i] = v[0] - a[0].f + a[i].f;
            }
        }
        ld sum = 0;
        rep(i, 0, n) sum += v[i];
        if(sum > s) hi = mid;
        else lo = mid;
    }
    vd v1(n);
    rep(i, 0, n) v1[a[i].s] = v[i];
    cout << fixed << setprecision(12);
    rep(i, 0, n) cout << v1[i] << nL;
    
    return 0;
}