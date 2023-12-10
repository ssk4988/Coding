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
        vl cnt(2); // 0 neg 1 pos
        rep(i, 0, n){
            ll v; cin >> v;
            vl cnt2(cnt);
            ll rem = min(abs(v), cnt[v > 0]);
            cnt2[v > 0] -= rem;
            cnt2[!(v > 0)] += rem;
            if(v != 0) v -= v / abs(v) * rem;
            cnt2[!(v > 0)] += abs(v);
            cnt = cnt2;
            // cout << cn << " " << cnt[0] << " "<< cnt[1] << " " << v << "\n";
        }
        cout << cnt[0] + cnt[1] << "\n";
    }
    
    return 0;
}
