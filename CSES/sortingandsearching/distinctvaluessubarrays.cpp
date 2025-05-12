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
    map<int, int> freq;
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int r = 0;
    ll ans = 0;
    rep(l, 0, n) {
        while(r < n && freq[a[r]] == 0) {
            freq[a[r]]++;
            r++;
        }
        ans += r-l;
        freq[a[l]]--;
    }
    cout << ans << "\n";
    
    return 0;
}
