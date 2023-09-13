#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ll days, hours, minutes, seconds; cin >> days >> hours >> minutes;
        ll res = 24 * 60 * days + 60 * hours + minutes;
        cout << res << "\n";
    }
}
