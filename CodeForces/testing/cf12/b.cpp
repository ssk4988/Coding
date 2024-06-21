#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        string str;
        cin >> str;

        bool good = true;
        if(str[0] != '1') good = false;
        rep(i, 1, sz(str)-1)
        {
            if (str[i] <= '9' && str[i] >= '1')
            {
            }
            else
                good = false;
        }
        if(str.back() <= '8' && str.back() >= '0'){} else good = false;
        cout << (good ? "YES" : "NO") << "\n";
    }

    return 0;
}
