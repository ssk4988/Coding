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
        ll ans = 0;
        rep(i, 1, n + 1){
            rep(j, i, n + 1){
                ll c = j * i;
                ll c1 = 0;
                set<int> ss;
                rep(k, 1, n + 1){
                    if(k == i) continue;
                    ss.insert(k);
                }
                bool works = true;
                for(int k = n; k > 0; k--){
                    if(k == j) continue;
                    auto it = ss.upper_bound(c / k);
                    if(it == ss.begin()){
                        works = false;
                        break;
                    }
                    it = prev(it);
                    c1 += k * *it;
                    ss.erase(it);
                }
                ans = max(ans, c1);
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
