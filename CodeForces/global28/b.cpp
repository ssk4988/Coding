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
    vi a(n, -1);
    int cur = 0;
    int idx = k-1;
    while(idx < n){
        a[idx] = cur++;
        idx += k;
    }
    // rep(i, 0, n){
    //     rep(t, 0, 2){
    //         int idx = t ? (k-1 + i) : (n - k - i);
    //         if(idx < 0 || idx >= n || a[idx] != -1) continue;
    //         a[idx] = cur++;
    //     }
    // }
    rep(i, 0, n){
        if(a[i] == -1) a[i] = cur++;
        cout << a[i]+1 << " ";
    }
    cout << "\n";
    
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
