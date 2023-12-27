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
        ll score = 0;
        vl l(n), r(n), c(n);
        rep(i, 0, n) cin >> l[i];
        rep(i, 0, n) cin >> r[i];
        rep(i, 0, n) cin >> c[i];
        sort(all(l)), sort(all(r)), sort(all(c));
        vl st;
        int cidx = n - 1;
        int lidx = 0, ridx = 0;
        vl ints;
        while(lidx < n || ridx < n){
            if(ridx >= n || (lidx < n && l[lidx] < r[ridx])){
                st.push_back(l[lidx]);
                lidx++;
            }
            else{
                ints.pb(r[ridx] - st.back());
                st.pop_back();
                ridx++;
            }
        }
        sort(all(ints));
        reverse(all(ints));
        rep(i, 0, n){
            score += ints[i] * c[i];
        }
        cout << score << nL;
    }
    
    return 0;
}
