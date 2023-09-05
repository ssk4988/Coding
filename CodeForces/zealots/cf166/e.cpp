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
        vl a(n), b(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n){
            cin >> b[i];
        }
        int ans = 0, numzeros = 0;
        vl pos, neg;
        rep(i, 0, n){
            ll c = b[i] - a[i];
            if(c == 0) numzeros++;
            else if(c > 0) pos.pb(c);
            else if(c < 0) neg.pb(-c);
        }
        sort(all(pos));
        sort(all(neg));
        // vi used(sz(pos));
        int posidx = 0;
        rep(i, 0, sz(neg)){
            while(posidx < sz(pos) && pos[posidx] < neg[i]) posidx++;
            if(posidx < sz(pos) && neg[i] <= pos[posidx]){
                // used[posidx++] = true;
                posidx++;
                ans++;
            }
        }
        int leftover = numzeros + sz(pos) - ans;
        ans += leftover / 2;
        cout << ans << nL;
    }
    
    return 0;
}
