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
    ll n, m, k; cin >> n >> m >> k;
    vl a(n), b(n);
    vi st;
    ll window = 0;
    rep(i, 0, 2*(n+m)) {
        if(i-m >= 0 && i-m < n) {
            window -= b[i-m];
        }
        if(i < n) {
            cin >> a[i];
            st.push_back(i);
        }
        while(window < k && sz(st)) {
            int x = st.back();
            if(x <= i-m) {
                st.pop_back(); continue;
            }
            ll amt = min(a[x]-b[x], k-window);
            b[x] += amt;
            window += amt;
            if(b[x] == a[x]) st.pop_back();
        }
    }
    cout << accumulate(all(b), 0LL) << "\n";
    
    
    return 0;
}
