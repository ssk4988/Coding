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
    auto getstr = [](string &str)->string{
        vector<char> odds, evens;
        rep(i, 0, sz(str)){
            (i % 2 == 0 ? evens : odds).pb(str[i]);
        }
        sort(all(evens));
        sort(all(odds));
        string res;
        rep(i, 0, sz(str)){
            if(i < sz(evens)) res.pb(evens[i]);
            if(i < sz(odds)) res.pb(odds[i]);
        }
        return res;
    };
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        string str; cin >> str;
        string ans;
        if(k % 2 == 1){
            ans = getstr(str);
        }
        else{
            if(n == k){
                ans = getstr(str);
                reverse(all(str));
                ans = min(ans, getstr(str));
            }
            else{
                sort(all(str));
                ans = str;
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}