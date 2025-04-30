#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
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
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vi c(a);
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    vi freq(sz(c));
    rep(i, 0, n) {
        a[i] = lower_bound(all(c), a[i]) - begin(c);
        freq[a[i]]++;
    }
    vvi ed(sz(c));
    int ans = 0;
    rep(i, 1, n) {
        if(a[i-1]+1 == a[i]) {
            ed[a[i-1]].pb(i-1);
        }
        if(a[i-1] == a[i]) ans++;
    }
    vi cand{-2};
    rep(i, 0, sz(c)) {
        vi new_cand;
        bool inc = false;
        for(int j : ed[i]) {
            for(int k : cand) {
                if(freq[i] == 1 || j != k+1) {
                    inc = true;
                    new_cand.pb(j);
                    break;
                }
            }
        }
        if(inc) {
            ans++;
            cand = new_cand;
        }
    }
    cout << (n-1-ans) << "\n";
    
    return 0;
}
