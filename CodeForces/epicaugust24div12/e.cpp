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
using a3 = array<ll, 3>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<a3> events(n); // cnt, color, time
        rep(i, 0, n){
            cin >> events[i][0] >> events[i][1];
        }
        ll t = 0;
        vl ans(n);
        vector<a3> st;
        auto fix = [&](a3 &e) {
            e[0] -= t - e[2];
            e[2] = t;
        };
        rep(i, 0, n){
            while(sz(st)){
                fix(st.back());
                fix(events[i]);
                if(st.back()[1] == events[i][1]){
                    events[i][0] += st.back()[0];
                    st.pop_back();
                    continue;
                }
                if(st.back()[0] < events[i][0]){
                    t += st.back()[0];
                    st.pop_back();
                    continue;
                }
                break;
            }
            st.push_back(events[i]);

            ans[i] = st[0][0] + st[0][2];
        }
        rep(i, 0 ,n){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
