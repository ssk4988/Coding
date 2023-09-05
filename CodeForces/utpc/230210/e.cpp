#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, k; cin >> n >> k;
    ll ans = 0;
    for(ll i = 1; i <= n; i++){
        ll left = i * k, right = i * (k + 1) - 1;
        left = max(left, 1LL), right = min(right, n);
        if(left <= right) ans += right - left + 1;
        // cout << i << " " << left << " " << right << "\n";
    }
    cout << ans << "\n";
    
}
