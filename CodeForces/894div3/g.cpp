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
        vl a(n);
        multiset<ll> difs, ss;
        rep(i, 0, n){
            cin >> a[i];
            ss.insert(a[i]);
        }
        ll pre = -1, difsum = 0;
        for(ll i : ss){
            if(pre != -1){ 
                difs.insert(i - pre);
                // difsum += i - pre;
            }
            pre = i;
        }
        int q; cin >> q;
        rep(i, 0, q){
            int idx; ll x; cin >> idx >> x;
            idx--;
            auto it = ss.find(a[idx]);
            if(it != ss.begin()){
                // difsum -= *it - *prev(it);
                difs.erase(difs.find(*it - *prev(it)));
            }
            if(it != ss.end() && next(it) != ss.end()){
                // difsum -= *next(it) - *it;
                difs.erase(difs.find(*next(it) - *it));
            }
            if(it != ss.begin() && it != ss.end() && next(it) != ss.end()){
                // difsum += *next(it) - *prev(it);
                difs.insert(*next(it) - *prev(it));
            }
            ss.erase(it);
            a[idx] = x;
            ss.insert(a[idx]);
            it = ss.find(a[idx]);
            if(it != ss.begin() && it != ss.end() && next(it) != ss.end()){
                // difsum -= *next(it) - *prev(it);
                difs.erase(difs.find(*next(it) - *prev(it)));
            }
            if(it != ss.begin()){
                // difsum += *it - *prev(it);
                difs.insert(*it - *prev(it));
            }
            if(it != ss.end() && next(it) != ss.end()){
                // difsum += *next(it) - *it;
                difs.insert(*next(it) - *it);
            }
            cout << (*ss.rbegin() + (difs.size() ? *difs.rbegin() : 0)) << " ";
        }

        cout << nL;
    }
    
    return 0;
}
