#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; cin >> n;
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ll s, p; cin >> s >> p;
            ans += s * ((p +4-1)/ 4);
        }
        cout << ans << "\n";
    }
}
