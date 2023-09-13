#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll tri(ll n){
    return n * (n + 1) / 2;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ll n; cin >> n;
        ll sum = 0;
        for(int i = 1; i <= n; i++){
            sum += i * tri(i+1);
        }
        cout << (cn + 1) << " " << n << " " << sum << "\n";
    }
}
