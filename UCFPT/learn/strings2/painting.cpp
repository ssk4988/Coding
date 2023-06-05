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
using vvl = vector<vl>;

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

ll MOD = 1e9 + 7;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}
bool DEBUG = false;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int pr, pc, mr, mc; cin >> pr >> pc >> mr >> mc;
    vvi p(pr, vi(pc)), m(mr, vi(mc));
    vvl pref(mr, vl(mc));
    ll phash = 0;
    vl po(2 * (mr * mc) + 1);
    po[0] = 1;
    int base = 3;
    rep(i, 1, sz(po)) po[i] = mod(po[i - 1] * base);
    rep(i, 0, pr){
        string str; cin >> str;
        rep(j, 0, pc){
            p[i][j] = (str[j] == 'x') + 1;
            phash = mod(phash + mod(p[i][j] * po[i * mc + j]));
        }
    }
    phash = mod(phash * po[mc * mr + mc]);


    rep(i, 0, mr){
        string str; cin >> str;
        rep(j, 0, mc){
            m[i][j] = (str[j] == 'x') + 1;
            pref[i][j] = mod(m[i][j] * po[i * mc + j]);
            if(i > 0) pref[i][j] = mod(pref[i][j] + pref[i - 1][j]);
            if(j > 0) pref[i][j] = mod(pref[i][j] + pref[i][j - 1]);
            if(i > 0 && j > 0) pref[i][j] = mod(pref[i][j] - pref[i - 1][j - 1]);
        }
    }
    int ans = 0;
    rep(i, 0, mr - pr + 1){
        rep(j, 0, mc - pc + 1){
            int i1 = i + pr - 1, j1 = j + pc - 1;
            ll curhash = pref[i1][j1];
            if(i > 0) curhash = mod(curhash - pref[i - 1][j1]);
            if(j > 0) curhash = mod(curhash - pref[i1][j - 1]);
            if(i > 0 && j > 0) curhash = mod(curhash + pref[i - 1][j - 1]);
            curhash = mod(curhash * po[(mr - i) * mc + (mc - j)]);
            if(curhash == phash){
                ans++;
                if(DEBUG) cout << i << " " << j << nL;
            }
        }
    }
    cout << ans << nL;    
    return 0;
}
