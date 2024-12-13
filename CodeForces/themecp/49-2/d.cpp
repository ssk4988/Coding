#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi p(n);
    set<int> mxi, mni;
    vi inv(n);
    rep(i, 0, n){
        cin >> p[i]; p[i]--;
        inv[p[i]] = i;
    }
    ll ans = 0;
    ll cur = 0;
    vii mxst, mnst;
    mxst.pb({n, -1});
    mnst.pb({-1, -1});
    mxi.insert(-1);
    mni.insert(-1);
    auto cont = [&](int idx) -> int {
        int lim = -1;
        auto it = mxi.upper_bound(idx);
        if(it != begin(mxi)){
            it = prev(it);
            lim = max(lim, *it);
        }
        it = mni.lower_bound(idx);
        if(it != begin(mni)){
            it = prev(it);
            lim = max(lim, *it);
        }
        return idx - lim;
    };
    rep(i, 0, n){
        pii nxt{p[i], i};
        while(mxst.back() < nxt) {
            auto [pmx, pi] = mxst.back();
            auto it = mni.lower_bound(pi);
            if(it != end(mni)) cur -= cont(*it);
            mxst.pop_back();
            mxi.erase(pi);
            if(it != end(mni)) cur += cont(*it);
        }
        while(mnst.back() > nxt) {
            auto [pmn, pi] = mnst.back();
            cur -= cont(pi);
            auto it = mni.upper_bound(pi);
            if(it != end(mni)) cur -= cont(*it);
            mnst.pop_back();
            mni.erase(pi);
            if(it != end(mni)) cur += cont(*it);
        }
        mxst.pb(nxt);
        mnst.pb(nxt);
        mni.insert(i);
        mxi.insert(i);
        ans += cur;
    }
    cout << ans << "\n";
    
    return 0;
}
