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
    int nc; cin >> nc;
    rep(cn, 0, nc){ 
        int n; cin >> n;
        vi a(n);
        map<int, int> freq;
        rep(i, 0, n) {
            cin >> a[i];
            freq[a[i]]++;
        }
        vii suff;
        vii ord;
        for(int i = n-1; i >= 0; i--) {
            if(sz(suff) == 0 || a[i] <= suff.back().f) {
                suff.pb({a[i], i});
            }
            ord.pb({a[i], i});
        }
        reverse(all(suff));
        sort(all(ord));
        vi use(n);
        vi res;
        int p = 0;
        for(auto [place, idx] : suff) {
            while(true){
                auto [p1, i1] = ord[p];
                if(use[i1]) p++;
                else break;
            }
            auto [p1, i1] = ord[p];
            if (p1+1 < place) break;
            use[idx] = true;
            res.pb(place);
        }
        while(p < sz(ord)) {
            if(use[ord[p].s]) {p++; continue;}
            res.pb(ord[p].f+1);
            p++;
        }
        for(int v : res) cout << v << " ";
        cout << "\n";
    }    
    
    return 0;
}
