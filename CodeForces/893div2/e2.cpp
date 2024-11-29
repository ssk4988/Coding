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

const int N = 1e6+10;
const int inf = 1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    int len = 0;
    vi seen(N, inf), pref(q+1), made(q+1, -1);
    vpi seenst, prefst, madest;
    vi lenst;
    vector<array<int, 4>> times;
    rep(i, 0, q)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int x;
            cin >> x;
            times.push_back({sz(lenst), sz(prefst), sz(seenst), sz(madest)});
            if(made[len] != -1){
                seenst.pb({made[len], seen[made[len]]});
                seen[made[len]] = inf;
                madest.pb({len, made[len]});
                made[len] = -1;
            }
            prefst.pb({len, pref[len]});
            // cerr << "pref " << i << " " << len << " " << x << endl;
            pref[len] = (len == 0 ? 0 : pref[len-1]) + (seen[x] >= len);
            if(seen[x] >= len) {
                if(seen[x] != inf){
                    madest.pb({seen[x], made[seen[x]]});
                    made[seen[x]] = -1;
                }
                seenst.pb({x, seen[x]});
                seen[x] = len;
                madest.pb({len, made[len]});
                made[len] = x;
            }
            lenst.pb(len);
            len++;
        }
        if (c == '-')
        {
            times.push_back({sz(lenst), sz(prefst), sz(seenst), sz(madest)});
            int k;
            cin >> k;
            lenst.pb(len);
            len -= k;
        }
        if (c == '!'){
            auto [lt, pt, st, mt] = times.back();
            times.pop_back();
            while(sz(lenst) > lt) len = lenst.back(), lenst.pop_back();
            while(sz(prefst) > pt) pref[prefst.back().f] = prefst.back().s, prefst.pop_back();
            while(sz(seenst) > st) seen[seenst.back().f] = seenst.back().s, seenst.pop_back();
            while(sz(madest) > mt) made[madest.back().f] = madest.back().s, madest.pop_back();
        }
        if (c == '?')
        {
            cout << (len == 0 ? 0 : pref[len-1]) << endl;
        }
    }

    return 0;
}
