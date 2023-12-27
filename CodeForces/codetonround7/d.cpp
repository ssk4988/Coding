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
        int n, q; cin >> n >> q;
        vi a(n);
        int sum = 0;
        set<int> ones;
        rep(i, 0, n){
            cin >> a[i];
            sum += a[i];
            if(a[i] == 1) ones.insert(i);
        }
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 1){
                int v; cin >> v;
                int evendif = 2 * n;
                if(sz(ones)){
                    evendif = min({evendif, 2 * (*ones.begin()), 2 * (n - 1 - (*ones.rbegin()))});
                }
                if(v > sum){
                    cout << "NO\n";
                    continue;
                }
                if((v - sum) % 2 == 0){
                    cout << "YES\n";
                    continue;
                }
                if(sum - evendif < v){
                    cout << "NO\n";
                }
                else cout << "YES\n";
            }
            else{
                int idx, v; cin >> idx >> v;
                idx--;
                sum -= a[idx];
                if(a[idx] == 1) ones.erase(idx);
                a[idx] = v;
                if(a[idx] == 1) ones.insert(idx);
                sum += a[idx];
            }
        }
    }
    return 0;
}
