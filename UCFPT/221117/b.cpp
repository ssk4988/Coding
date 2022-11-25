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
    int n;
    cin >> n;
    rep(i, 0, n)
    {
        vi digs;
        string str;
        cin >> str;
        ll val = 0;
        ll base = 60;
        while (str.find(',') != -1)
        {
            val *= base;
            if (str.find(',') > 0)
                val += stoi(str.substr(0, str.find(',')));
            str.erase(str.begin(), str.begin() + str.find(',') + 1);
        };
        val *= base;
        if (str.length() > 0)
        {
            
            val += stoi(str);
        }
        cout << val << nL;
    }

    return 0;
}