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
        string s;
        cin >> s;
        // if (s == "()")
        // {
        //     cout << "NO\n";
        //     continue;
        // }
        int n = sz(s);
        string str1, str2;
        rep(i, 0, n)
        {
            str1.pb('(');
            str1.pb(')');
            str2.pb('(');
        }
        rep(i, 0, n) str2.pb(')');
        if (str1.find(s) == -1)
        {
            cout << "YES\n";
            cout << str1 << nL;
            continue;
        }
        else if (str2.find(s) == -1)
        {
            cout << "YES\n";
            cout << str2 << nL;
            continue;
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}
