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
    vi gn(2000);
    // cout << 1 << nL;
    // cout << 2 << nL;
    int pr = 0;
    rep(i, 1, 2000){
        set<int> gnnext;
        rep(j, 1, i){
            if(i - j <= j) continue;
            gnnext.insert(gn[j] ^ gn[i - j]);
        }
        int mex = 0;
        for(int i : gnnext){
            if(i == mex){
                mex++;
            }
            else break;
        }
        gn[i] = mex;
        // cout << "gn of " << i << " is " << gn[i] << nL;
        if(gn[i] == 0){
            // cout << i << " " << (i - pr) << nL;
            pr = i;
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        if(n >= 2000 || gn[n] > 0){
            cout << "first" << nL;
        }
        else{
            cout << "second" << nL;
        }
    }
    
    return 0;
}
