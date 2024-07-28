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
    // int nc; cin >> nc;
    // rep(cn, 0, nc){
    int n, q;
    cin >> n >> q;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    rep(_, 0, q)
    {
        int l, r;
        cin >> l >> r;
        l--;
        if (r - l >= 100)
        {
            cout << "YES\n";
            continue;
        }
        vl cur;
        rep(i, l, r) cur.pb(a[i]);
        sort(all(cur));
        vi works;
        rep(i, 0, sz(cur) - 3 + 1)
        {
            if (cur[i] + cur[i + 1] > cur[i + 2])
            {
                works.pb(i);
            }
        }
        if(r - l >= 50){
            cout << (sz(works) > 0 ? "YES" : "NO") << "\n";
            continue;
        }
        if (sz(works) == 0)
        {
            cout << "NO\n";
            continue;
        }
        bool yes = works[0] + 3 <= works.back();
        if(yes){
            cout << "YES\n";
            continue;
        }
        rep(i, 0, sz(cur) - 6 + 1) {
            // if(i + 6 > sz(cur)) break;
            rep(j, 1, 6){
                rep(k, j+1, 6){
                    if(cur[i] + cur[i + j] <= cur[i + k]) continue;
                    vi other;
                    rep(l, 1, 6){
                        if(l != j && l != k) other.pb(l);
                    }
                    if(cur[other[0] + i] + cur[other[1] + i] > cur[other[2] + i]){
                        yes = true;
                        goto fnd;
                    }
                }
            }
        }
        fnd:
        cout << (yes ? "YES" : "NO") << "\n";
    }
    // }

    return 0;
}
