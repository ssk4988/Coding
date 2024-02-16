#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    int ans = 1;
    rep(i, 0, n){
        int sum = a[i] + (i > 0 ? a[i-1] : 0);
        if(sum <= k) ans = max(ans, i + 1);
    }
    cout << ans << "\n";

    return 0;
}