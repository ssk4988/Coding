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
using a3 = array<int, 3>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<a3> events;
        vi bs(n);
        rep(i, 0, n){
            int l, r, a, b; cin >> l >> r >> a >> b;
            bs[i] = b;
            events.pb({l, 0, i});
            events.pb({r, 10, i});
            events.pb({a, 1, i});
            events.pb({b, 2, i});
        }
        multiset<int> reachable;
        int q; cin >> q;
        vi ans(q);
        map<int, int> nex;
        rep(i, 0, q){
            cin >> ans[i];
            events.pb({ans[i], 3, i});
        }
        sort(all(events));
        for(auto [x, t, idx] : events){
            if(t == 0){
                reachable.insert(bs[idx]);
            }
            if(t == 10){
                reachable.erase(reachable.find(bs[idx]));
            }
            if(t == 2 || t == 3){
                // reachable
                if(sz(reachable) == 0) nex[x] = x;
                else nex[x] = max(x, *reachable.rbegin());
                // jmp[x] = 
            }
        }
        map<int, int> rl, rrl;
        for(auto [key, val] : nex){
            rl[key] = sz(rl);
            rrl[rl[key]] = key;
        }
        int k = sz(rl);
        vvi jmp(k, vi(20));
        for(auto [key, val] : nex){
            assert(rl.count(val));
            jmp[rl[key]][0] = rl[val];
        }
        rep(i, 1, 20){
            rep(j, 0, k){
                jmp[j][i] = jmp[jmp[j][i - 1]][i - 1];
            }
        }
        rep(i, 0, q){
            ans[i] = max(ans[i], rrl[jmp[rl[ans[i]]].back()]);
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
