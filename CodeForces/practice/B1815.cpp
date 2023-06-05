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
        int n; cin >> n;
        auto connect = [&](int x)->int{
            cout << "+ " << x << nL;
            cout.flush();
            int k; cin >> k;
            return k;
        };
        connect(n + 1);connect(n + 2);
        auto query = [&](int i, int j)->int{
            assert(i > 0); assert(j > 0);
            cout << "? " << i << " " << j << nL;
            cout.flush();
            int k; cin >> k;
            return k;
        };
        vi stuff(n + 1);
        int best = 0;
        rep(i, 2, n + 1){
            stuff[i] = query(1, i);
            if(stuff[i] > stuff[best]) best = i;
        }
        stuff = vi(n + 1);
        rep(i, 1, n + 1){
            if(i == best) continue;;
            stuff[i] = query(best, i);
        }
        vi rev(n + 1), fr;
        int cur = 1;
        fr.pb(-1);
        fr.pb(cur);
        for(int i = 0; true; i++){
            int nex = i % 2 == 0 ? (n + 1 - cur) : (n + 2 - cur);
            if(nex == cur) break;
            rev[nex] = 1 + rev[cur];
            cur = nex;
            fr.pb(cur);
        }
        vi p1(n + 1), p2(n + 1);
        rep(i, 1, n + 1){
            p1[i] = fr[1 + stuff[i]];
            p2[i] = fr[n - stuff[i]];
        }
        cout << "! ";
        rep(i, 1, n + 1){
            cout << p1[i] << " ";
        }
        rep(i, 1, n + 1){
            cout << p2[i] << " ";
        }
        cout << nL;
        cout.flush();
        int t;
        cin >> t;
        if(t == -2) return 0;
    }
    

    
    return 0;
}
