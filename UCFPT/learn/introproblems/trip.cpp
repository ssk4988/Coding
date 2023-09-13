#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ld a1, a2, p1, p2; cin >> a1 >> a2 >> p1 >> p2;
        ld res = a1 * p1 + a2 * p2;
        cout << fixed << setprecision(2) << res << "\n";
    }
}
