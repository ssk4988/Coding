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
    int n, a, b; cin >> n >> a >> b;
    vi ops(n);
    rep(i, 0, n){
        cin >> ops[i];
    }
    vvi dp(a + 1, vi(b + 1));
    rep(cdsum, 0, a + b + 1){
        vi c(1 + min(cdsum, a));
        int plen = 1, slen = 1, prep = 0, srep = min(cdsum, a);
        bool ps = srep = prep;
        rep(i, 0, n){
            if(ops[i] > 0){
                int subamount = min(ops[i], prep);
                if(ops[i] > prep){
                    plen += ops[i] - prep;
                }
                prep -= subamount;
                srep -= min(srep, ops[i]);
            }
            if(ops[i] < 0){
                
                int subamount = min(-ops[i], a - srep);
                if(-ops[i] > a - srep){
                    slen += -ops[i] - (a - srep);
                }
                srep += subamount;
                prep += min(a - prep, -ops[i]);
            }
            if(!ps && srep == prep){
                plen = slen = min(cdsum, a);
                ps = true;
            }
        }
        rep(i, 0, plen){
            dp[i][cdsum - i] = prep;
        }
        rep(i, 0, min(cdsum, a)){
            if(i < plen){
                dp[i][cdsum - i] = prep;
            }
        }
    }
    
    return 0;
}
