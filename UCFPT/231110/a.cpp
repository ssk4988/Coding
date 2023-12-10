#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){ 
        vector<int> a(4);
        for(int i = 0; i < 4; i++) cin >> a[i];
        swap(a[2], a[3]);
        vector<int> b(4);
        for(int i = 0; i < 4; i++) cin >> b[i];
        swap(b[2], b[3]);
        bool works = false;
        for(int i = 0; i < 4; i++){
            rotate(b.begin(), b.begin() + 1, b.end());
            if(a == b) works = true;
        }
        cout << "Case #" << (cn + 1) << ": " << (works ? "POSSIBLE" : "IMPOSSIBLE") << "\n";
    }
    return 0;
}
