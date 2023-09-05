#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r1, r2; cin >> r1 >> r2;
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int u; cin >> u;
        int u1 = u;
        int score = min(1000, u) * r1;
        u -= min(1000, u);
        score += u * r2;
        cout << u1 << " " << score << "\n";
    }
}
