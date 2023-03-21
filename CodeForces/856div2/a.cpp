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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vector<string> vs(2 * n - 2);
        vector<vector<string>> vs1(n);
        vector<string> vs2;
        rep(i, 0, 2 * n - 2)
        {
            string str; cin >> str;
            vs1[str.length()].pb(str);
        }
        bool isPal = true;
        rep(i, 1, n){
            reverse(all(vs1[i][1]));
            rep(j, 0, i){
                if(vs1[i][0][j] != vs1[i][1][j]) isPal = false;
            }
        }
        cout << (isPal ? "YES" : "NO") << nL;
    }

    return 0;
}
