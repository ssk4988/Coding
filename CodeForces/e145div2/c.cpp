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
        int n, k; cin >> n >> k;
        vi ans(n, -1000);
        int lastone = 0;
        for(; lastone * (lastone + 1) / 2 <= k; lastone++){

        }
        lastone--;
        rep(i, 0, lastone){
            ans[i] = lastone + 1 - i;
        }
        k -= lastone * (lastone + 1) / 2;
        if(lastone < n){
            ans[lastone] = -1 * (lastone + 1 -k) * ((lastone + 1 -k) + 1) / 2;
        }
        rep(i, 0, n){
            cout << ans[i];
            if(i + 1 < n){
                cout << " ";
            }
        }
        cout << nL;

    }
    
    return 0;
}
