#include <bits/stdc++.h>
using namespace std;

using ld = long double;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; ld d; cin >> n >> d;
        ld ans = 0;
        for(int i = 0; i < n; i++){
            ld v; cin >> v;
            ans += d / v;
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
}
