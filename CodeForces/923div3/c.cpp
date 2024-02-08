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
        int n, m, k; cin >> n >> m >> k;
        vi mask(k);
        vi cnt(4);
        rep(i, 0, n){
            int a; cin >> a;
            a--;
            if(a < k) mask[a] |= 1;
        }
        rep(i, 0, m){
            int a; cin >> a;
            a--;
            if(a < k) mask[a] |= 2;
        }
        rep(i, 0, k){
            cnt[mask[i]]++;
        }
        if(cnt[0] > 0){
            cout << "NO\n";
        }
        else{
            cout << ((cnt[1] <= k/2 && cnt[2] <= k/2) ? "YES" : "NO") << nL;
        }
    }
    
    return 0;
}
