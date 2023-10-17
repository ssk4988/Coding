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
        vl c(n);
        map<ll, int> rm;
        rep(i, 0, n) {
            cin >> c[i];
            rm[c[i]] = i;
        }
        ll k; cin >> k;
        vector<pair<ll, int>> st;
        st.pb({0, -1});
        for(auto [key, val] : rm){
            if(val > st.back().s){
                st.pb({key, val});
                // cout << "pushed " << key << " " << val << nL;
            }
        }
        vi ans(n);
        ll cur = INT_MAX;
        rep(i, 1, sz(st)){
            auto [cost, ind] = st[i];
            auto [prevcost, prevind] = st[i - 1];
            ll dif = cost - prevcost;
            ll exc = min(cur, k / dif);
            cur = exc;
            k -= exc * dif;
            ans[ind] += exc;
            if(prevind >= 0) ans[prevind] -= exc;
        }
        for(int i = n - 2; i >= 0; i--){
            ans[i] += ans[i + 1];
        }
        rep(i, 0, n){
            cout << ans[i] << " ";
        }
        cout << nL;

    }
    
    return 0;
}
