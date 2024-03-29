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

const int N = 1000;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, init; cin >> n >> m >> init;
        bitset<N> bs, prevbs;
        init--;
        prevbs[init] = 1;
        rep(i, 0, m){
            int r; char t; cin >> r >> t;
            if(t == '0' || t == '?') {
                bs |= ((prevbs << r) | (prevbs >> (n - r)));
            }
            if(t == '1' || t == '?'){
                bs |= ((prevbs >> r) | (prevbs << (n - r)));
            }
            swap(bs, prevbs);
            bs.reset();
        }
        vi ans;
        rep(i, 0, n){
            if(prevbs[i]) ans.pb(i);
        }
        cout << sz(ans) << "\n";
        for(int i : ans) cout << (i+1) << " ";
        cout << "\n";
    }
    
    return 0;
}
