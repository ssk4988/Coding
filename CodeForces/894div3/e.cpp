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
        int n, m;
        ll d;
        cin >> n >> m >> d;
        vl a(n);
        ll best = 0;
        multiset<ll> b;
        ll bsum = 0;
        rep(i, 0, n)
        {
            cin >> a[i];
            if (a[i] >= 0 && (b.size() < m || *b.begin() < a[i]))
            {
                if (b.size() == m)
                {
                    bsum -= *b.begin();
                    b.erase(b.begin());
                }
                if(a[i] >= 0){
                    b.insert(a[i]);
                    bsum += a[i];
                }
            }
            best = max(best, bsum - d * (i + 1));
        }
        cout << best << nL;
    }

    return 0;
}
