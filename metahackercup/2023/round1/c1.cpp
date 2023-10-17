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
        string str; cin >> str;
        vector<bool> res(n);
        rep(i, 0, n) res[i] = str[i] == '1';
        int q; cin >> q;
        vector<bool> updates(n);
        rep(i, 0, q){
            int idx; cin >> idx; idx--;
            updates[idx] = updates[idx] ^ 1;
        }
        rep(i, 0, n){
            if(updates[i]){
                for(int j = i; j < n; j += i + 1) res[j] = res[j] ^ 1;
            }
        }
        int ans = 0;
        rep(i, 0, n){
            if(res[i]){
                ans++;
                for(int j = i; j < n; j += i + 1) res[j] = res[j] ^ 1;
            }
        }
        cout << "Case #" << (cn + 1) << ": " << ans << nL;
    }
    
    return 0;
}
