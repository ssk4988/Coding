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
        int n, c, k; cin >> n >> c >> k;
        string str; cin >> str;
        vi a(n);
        rep(i, 0, n) a[i] = str[i] - 'A';
        vi bad(1 << c);
        vi freq(c);
        rep(i, 0, k-1){
            freq[a[i]]++;
        }
        rep(i, k-1, n){
            freq[a[i]]++;
            if(i >= k){
                freq[a[i-k]]--;
            }
            int mask = 0;
            rep(j, 0, c){
                if(freq[j]) mask |= 1 << j;
            }
            bad[mask] = true;
        }
        bad[1 << (a.back())] = true;
        rep(t, 0, c){
            rep(mask, 0, sz(bad)){
                if(((mask >> t) & 1) && bad[mask ^ (1 << t)]) bad[mask] = true;
            }
        }
        int ans = c;
        rep(mask, 0, sz(bad)){
            if(!bad[mask]) ans = min(ans, c - __builtin_popcount(mask));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
