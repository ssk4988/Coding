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
    vi st;
    vl a(n);
    vector<vl> pos(n);
    rep(i, 0, n) {
        cin >> a[i];
        while(sz(st) && a[st.back()] < a[i]) pos[st.back()].push_back(i), st.pop_back();
        if(sz(st)) pos[i].push_back(st.back());
        st.push_back(i);
    }
    ll ans = 0;
    rep(i, 0, n) {
        if(sz(pos[i])) {
            int add = 1e9;
            for(int j : pos[i]) add = min(add, abs(i - j));
            ans += add;
        }
    }
    cout << ans << "\n";
    return 0;
}
