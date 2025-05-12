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
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vi par(n+1, n);
    vii st;
    st.push_back({int(1e9+1), n});
    for(int i = n-1; i >= 0; i--) {
        while(st.back().f <= a[i]) st.pop_back();
        par[i] = st.back().s;
        st.push_back({a[i], i});
    }
    vvi jmp(20, par);
    rep(p, 0, sz(jmp)-1) {
        rep(i, 0, n+1) {
            jmp[p+1][i] = jmp[p][jmp[p][i]];
        }
    }
    rep(qid, 0, q) {
        int l, r; cin >> l >> r; l--;
        int ans = 1;
        int u = l;
        for(int i = sz(jmp)-1; i >= 0; i--) {
            if(jmp[i][u] < r) {
                ans += 1 << i;
                u = jmp[i][u];
            }
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
