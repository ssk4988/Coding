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
        int n, m, d; cin >> n >> m >> d;
        vi s(m);
        rep(i, 0, m){
            cin >> s[i];
        }
        s.pb(n + 1);
        bool hasfirst = s[0] == 1;
        if(!hasfirst){
            vi s1(s);
            s = vi(1, 1);
            for(int i : s1) s.pb(i);
            m++;
        }

        m++;
        vi cnt(m), suff(m);
        int last = n + 1;
        for(int i = m - 1; i >= 0; i--){
            cnt[i] = (last - s[i] + d - 1) / d;
            suff[i] = cnt[i];
            if(i + 1 < sz(suff)) suff[i] += suff[i + 1];
            last = s[i];
        }
        int best = suff.front();
        vi bests;
        vi pref(m);
        rep(i, 0, m){
            pref[i] = cnt[i];
            if(i) pref[i] += pref[i - 1];
        }
        if(hasfirst){
            best = suff.front();
            bests.pb(0);
        }
        rep(i, 1, m - 1){
            int curscore = suff[i + 1] + pref[i - 1] - cnt[i - 1] + (s[i + 1] - s[i - 1] + d - 1) / d;
            if(curscore < best){
                best = curscore;
                bests.clear();
                bests.pb(i);
            }
            else if(curscore == best) bests.pb(i);
        }
        cout << best << " " << sz(bests) << nL;
    }
    
    return 0;
}
