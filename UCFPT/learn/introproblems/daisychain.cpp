#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll chain(ll k, ll c){
    return (c - 1) * (k - 1) + k;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ll n, p, g; cin >> n >> p >> g;
        ll ans = n / g * chain(p, g);
        if(n % g){
            ans += chain(p, n % g);
        }
        cout << ans << "\n";
    }
}
