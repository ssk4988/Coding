#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k; ll t;
    cin >> n >> k >> t;
    vl a(n);
    for(ll i = 0; i < n; i++){
        a[i] = i;
    }
    vl ans(a);
    vl ka(k);
    for(ll i = 0; i< k; i++){
        cin >> ka[i];
    }
    if(k != 1){
        ll pnter = 0;
        for(ll i = 0; i < n; i++){
            while(pnter + 1 < k && ka[pnter + 1] <= i) pnter++;
            ll inc = i - ka[pnter];
            ll dif = (ka[(pnter + 1) % k] + 2 * n - ka[pnter]) % n;
            ll shift = t - inc + dif - 1 < 0 ? 0 : (t - inc + dif - 1) / dif;
            shift %= n;
            // cout << "shift for i=" << i << ": " << shift << " pnter: " << pnter << " inc: " << inc << " dif: " << dif << " actual shift: " << (shift * dif) % n << "\n";
            ans[(i + ((shift * dif) % n)) % n] = i;
        }

    }
    for(ll i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
