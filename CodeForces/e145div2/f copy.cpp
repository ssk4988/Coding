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
        int n; ll k;
        cin >> n >> k;
        vl a(n); vi b(n);
        vl pref(n * 2);
        rep(i, 0, n){
            cin >> a[i];
            a.pb(a[i]);
        }
        vi fcnt(2);
        rep(i, 0, n){
            cin >> b[i];
            b[i]--;
            fcnt[b[i]]++;
            b.pb(b[i]);
        }
        rep(i, 0, 2 * n){
            pref[i] = a[i];
            if(i > 0) pref[i] += pref[i - 1];
        }
        vl ans(n);
        if(fcnt[0] == n || fcnt[1] == n){
            rep(i, 0, n){
                ans[i] = pref[n - 1];
                if(fcnt[1] == n) ans[i] *= 2;
            }
        }
        else{
            vector<pair<int, ll>> nex(2 * n);
            int pre = 2 * n;
            ll dis = 0;
            for(int i = 2 * n - 1; i >= 0; i--){
                dis += a[i];
                if(b[i] == 0){
                    nex[i] = {pre, dis - min(k, dis)};
                    dis = 0; pre = i;
                }
                else{
                    nex[i] = {pre, dis};
                }
            }
            auto dist = [&](int l, int r) -> ll{
                ll res = pref[r - 1];
                if(l > 0) res -= pref[l - 1];
                return res;
            };
            ll curans = 0;
            deque<pair<int, ll>> dq;
            curans += nex[0].s;
            dq.pb({nex[0].f, nex[0].s});
            while(dq.back().f < 0 + n){
                ll d;int dest;
                if(nex[dq.back().f].f > n){
                    d = dist(dq.back().f, n);
                    dest = n;
                    if(b[dq.back().f] == 0){
                        d = d - min(k, d);
                    }
                }
                else{
                    d = nex[dq.back().f].s;
                    dest = nex[dq.back().f].f;
                }
                curans += d;
                dq.pb({dest, d});
            }
            ans[0] = curans;
            rep(i, 1, n){
                if(dq.front().f <= i){
                    curans -= dq.front().s;
                    dq.pop_front();
                }
                else{
                    curans -= dq.front().s;
                    dq.front().s = dist(i, dq.front().f);
                    if(b[i] == 0){
                        dq.front().s = dq.front().s - min(k, dq.front().s);
                    }
                    curans += dq.front().s;
                }
                if(b[dq.back().f] == 1){
                    // remove old section
                    curans -= dq.back().s;
                    dq.pop_back();

                }
                while(dq.back().f < i + n){
                    ll d;int dest;
                    if(nex[dq.back().f].f > i + n){
                        d = dist(dq.back().f, i + n);
                        dest = i + n;
                        if(b[dq.back().f] == 0){
                            d = d - min(k, d);
                        }
                    }
                    else{
                        d = nex[dq.back().f].s;
                        dest = nex[dq.back().f].f;
                    }
                    
                    curans += d;
                    dq.pb({dest, d});
                }

                
                ans[i] = curans; 
            }
            rep(i, 0, n){
                ans[i] += pref[n - 1];
            }
        }
        rep(i, 0, n){
            cout << ans[i] << " ";
        }
        cout << nL;
        
    }
    
    return 0;
}