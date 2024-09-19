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

const ll MOD = 1e9+7; 
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t, k; cin >> t >> k;
    int LIM = 1e5 + 100;
    vl ans(LIM);
    ans[0] = 1;
    rep(i, 0, LIM) {
        if(i + 1 < LIM) (ans[i+1] += ans[i]) %= MOD;
        if(i + k < LIM) (ans[i+k] += ans[i]) %= MOD;
    }
    rep(i, 1, LIM) {
        (ans[i] += ans[i-1]) %= MOD;
    }
    ans.insert(ans.begin(), 0);
    rep(i, 0, t){
        int a, b; cin >> a >> b; b++;
        ll res = ans[b] - ans[a];
        (res += MOD) %= MOD;
        cout << res << "\n";
    }
    
    return 0;
}
