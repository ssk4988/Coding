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
        int r, c; cin >> r >> c;
        vector<vi> diag(r + c - 1);
        rep(i, 0, r){
            string str; cin >> str;
            rep(j, 0, c){
                if(str[j] == '1'){
                    diag[i + j].pb(- i);
                }
            }
        }
        // d1 = i + j
        // d2 = j - i + r - 1?
        rep(i, 0, sz(diag)){
            sort(all(diag[i]));
            // reverse(all(diag[i]));
        }
        // reverse(all(diag));
        int ans = 0;
        vector<set<int>> ss(2);
        rep(d, 0, sz(diag)){
            if(diag[d].size() == 0) continue;
            if(ss[d % 2].upper_bound(diag[d].back()) != ss[d % 2].end()){
                ss[d % 2].erase(ss[d % 2].upper_bound(diag[d].back()));
            }
            else{
                ans++;
            }
            ss[d % 2].insert(diag[d][0]);
        }
        cout << ans << nL;
    }
    
    return 0;
}
