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
        vl pref(n);
        rep(i, 1, n) cin >> pref[i];
        for (int i = n - 1; i > 0; i--)
            pref[i] -= pref[i - 1];
        ll rem = -1;
        int numabove = 0;
        vl freq(n + 1);
        rep(i, 1, n)
        {
            if (pref[i] > n)
            {
                rem = pref[i];
                numabove++;
            }
            else
                freq[pref[i]]++;
        }
        vl missing;
        if (rem == -1)
        {
            rep(i, 1, n + 1){
                if(freq[i] == 2){
                    rem = i;
                    numabove++;
                }
            }
        }
        rep(i, 1, n + 1) if(freq[i] == 0) missing.pb(i);
        bool works = numabove == 1 && sz(missing) == 2;
        if(works && rem != missing[0] + missing[1]) works = false;
        if(sz(missing) == 1) works = true;
        cout << (works ? "YES" : "NO") << nL;
    }

    return 0;
}