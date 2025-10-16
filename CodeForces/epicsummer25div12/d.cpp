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


void solve() {

    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vi b(a);
    sort(all(b));
    int kth = b[k-1];
    while(b.back() > kth) b.pop_back();
    int slack = sz(b) - (k-1);
    {
        vi a2;
        for(auto x : a) if(x <= kth) a2.pb(x);
        a = a2;
    }
    n = sz(a);
    int l = 0, r = n-1;
    int use = 0;
    while(l <= r) {
        if(a[l] != a[r]) {
            if(max(a[l], a[r]) < kth) {
                cout << "NO\n";
                return;
            }
            use++;
            if(a[l] == kth) l++;
            else r--;
        } else l++, r--;
    }
    cout << (use <= slack ? "YES" : "NO") << "\n";
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
