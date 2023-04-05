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
        int n;
        ll k; cin >> n >> k;
        vl a(n); vi b(n);
        vl pref(n * 2);
        vl ans(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi fcnt(2);
        rep(i, 0, n){
            cin >> b[i];
            fcnt[b[i] - 1]++;
        }
        if(fcnt[0] == n || fcnt[1] == n){
            rep(i, 0, n){
                ans[i] = pref.back();
                if(fcnt[1] == n) ans[i] += pref.back();
            }
        }
        else{
            vector<pair<int, ll>> nex(n);
            ll pre = 2 * n, dis = 0;
            rep(i, 0, n){
                a.pb(a[i]);
                b[i]--;
                b.pb(b[i]);
            }
            rep(i, 0, n * 2){
                pref[i] = a[i];
                if(i > 0) pref[i] += pref[i - 1];
            }
            auto dist = [&](int l, int r) -> ll{
                ll res = pref[r - 1];
                if(l > 0) res -= pref[l - 1];
                return res;
            };
            ll base = pref[n - 1];
            for(int i = 2 * n - 1; i >= 0; i--){
                dis += a[i];
                nex[i] = {pre, dis - min(k, dis)};
                if(b[i] == 0){
                    pre = i;
                    dis = 0;
                }
            }
            ll curans = 0;
            deque<pair<int, ll>> dq;
            dq.pb({nex[0]});
            curans += nex[0].s;
            while(dq.back().f != 0 + n){
                if(nex[dq.back().f].f > 0 + n){
                    assert(b[dq.back().f] == 0);
                    ll d = dist(dq.back().f, nex[dq.back().f].f);
                    d = d - min(k, d);
                    dq.pb({0 + n, d});
                    curans += d;
                }
                else{
                    curans += nex[dq.back().f].s;
                    dq.pb(nex[dq.back().f]);
                }
            }
            ans[0] = curans;
            rep(i, 1, n){
                while(dq.front().f < i){
                    curans -= dq.front().s;
                    dq.pop_front();
                }
                ll d = dist(i, dq.front())
                
            }
        }
        rep(i, 0, n){
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
