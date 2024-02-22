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
        string s; cin >> s;
        int ans = 10;
        vi left = {5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0};
        rep(b, 0, 2){
            vi sc(2);
            rep(i, 0, 10){
                if(left[i] + sc[i&1] < sc[1-(i&1)] || left[i+1] + sc[1-(i&1)] < sc[i&1]){
                    ans = min(ans, i);
                    break;
                }
                if(s[i] == '1') sc[i&1]++;
                else if(s[i] == '0') ;
                else sc[i&1] += (b == (i&1));
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}
