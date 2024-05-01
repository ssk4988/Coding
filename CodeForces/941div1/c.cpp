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
        bool right = true;
        int mindex = 0, maxdex = 0, cur = 0;
        string str; cin >> str;
        int pre = -1;
        for(char c : str){
            int v = c - '0';
            if(pre == -1){
                pre = v;
                continue;
            }
            if(v != pre){
                cur += right ? 1 : -1;
                mindex = min(mindex, cur);
                maxdex = max(maxdex, cur);
            } else{
                right = !right;
            }
            pre = v;

        }
        cout << (maxdex - mindex + 1) << nL;
    }
    
    return 0;
}
