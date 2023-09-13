#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        int n; cin >> n;
        multiset<ll> ss;
        for(int i = 0; i < n; i++){
            ll v; cin >> v;
            ss.insert(v);
        }
        ll ans = 0;
        for(int i = 0; i < n - 1; i++){
            ll v1 = *ss.begin();
            ss.erase(ss.begin());
            ll v2 = *ss.begin(); 
            ss.erase(ss.begin());
            ans += v1 + v2;
            ss.insert(v1 + v2);
        }
        cout << ans << "\n";
    }
}
