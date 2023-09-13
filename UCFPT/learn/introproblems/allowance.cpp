#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ll v; cin >> v;
        int ans = 0;
        for(int i = 35; i >= 0; i--){
            if((1LL << i) - 1 <= v){
                cout << i << " " << ((1LL << i) - 1) << "\n";
                break;
            }
        }
    }
}
