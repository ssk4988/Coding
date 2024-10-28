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

#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi h(n);
    rep(i, 0, n){
        cin >> h[i];
    }
    int hs;
    {
        vi c(h);
        sort(all(c));
        hs = sz(c);
        c.erase(unique(all(c)), end(c));
        for(int &i : h) i = lower_bound(all(c), i) - begin(c);
    }
    vvi bucket(hs);
    rep(i, 0, n) bucket[h[i]].push_back(i);
    int q; cin >> q;
    rep(_, 0, q){
        int k; cin >> k;
        vi firstlower(n, -1), lastlower(n, -1);
        set<int> idx;
        rep(i, 0, hs){
            for(int j : bucket[i]) {
                auto it = idx.upper_bound(j);
                if(it != end(idx)){
                    firstlower[j] = *it;
                    if(firstlower[j] > j + k) firstlower[j] = -1;
                }
                it = idx.upper_bound(j + k);
                if(it != begin(idx)){
                    it--;
                    lastlower[j] = *it;
                    if(lastlower[j] <= j) lastlower[j] = -1;
                }
            }
            for(int j : bucket[i]) idx.insert(j);
        }
        vi ans(n, 1e9);
        ans[0] = 0;
        set<pii> s;
        int r = 0;
        rep(i, 0, n){
            while(r < n && r <= i + k) s.insert({h[r], r++});
            s.erase({h[i], i});
            if(sz(s)) {
                auto it = prev(end(s));
                ans[it->second] = min(ans[it->second], ans[i] + 1);
                it = s.lower_bound({h[i], -1});
                if(it != begin(s)){
                    it--;
                    ans[it->second] = min(ans[it->second], ans[i]);
                }
            }
            if(firstlower[i] != -1) ans[firstlower[i]] = min(ans[firstlower[i]], ans[i]);
            if(lastlower[i] != -1) ans[lastlower[i]] = min(ans[lastlower[i]], ans[i]);
        }
        cout << ans[n-1] << "\n";
    }
    
    return 0;
}
