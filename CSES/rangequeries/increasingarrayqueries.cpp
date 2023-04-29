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
    int n, q; cin >> n >> q;
    vl a(n), pref(n);
    rep(i, 0, n){
        cin >> a[i];
        pref[i] = a[i];
        if(i > 0) pref[i] += pref[i - 1];
    }
    vector<vpi> queries = vector<vpi>(n);
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--,b--;
        queries[a].pb({b, i});
    }
    vl ans(q);
    vi st;
    vl sumst;
    // ll sumst = 0;
    for(int i = n - 1; i >= 0; i--){
        while(st.size() && a[st.back()] < a[i]){
            int bk = st.back();
            st.pop_back();
            sumst.pop_back();
            // sumst -= a[bk] * ((st.size() ? st.back() : n) - bk);
        }
        int bk = st.size() ? st.back() : n;
        st.pb(i);
        sumst.pb((sumst.size() ? sumst.back() : 0) + a[i] * (bk - i));
        // sumst += a[i] * (bk - i);
        for(pi &p : queries[i]){
            auto [j, idx] = p;
            ll curtop = sumst.back();
            if(j + 1 < n){
                int lo = 0, hi = st.size() - 1;
                while(lo < hi){
                    int mid = lo + (hi - lo) / 2;
                    if(st[mid] <= j + 1){
                        hi = mid;
                    }
                    else{
                        lo = mid + 1;
                    }
                }
                ll excl = sumst[lo] - a[st[lo]] * abs(j + 1 - st[lo]);
                curtop -= excl;
            }
            ans[idx] = curtop - (pref[j] - (i > 0 ? pref[i - 1] : 0));
        }

    }
    rep(i, 0, q){
        cout << ans[i] << nL;
    }

    
    return 0;
}