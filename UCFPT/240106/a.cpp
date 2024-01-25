#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int k; cin >> k;
    vi a(n);
    int ans = 0;
    for(int i = 0; i < k; i++){
        int v; cin >> v;
        for(int j = v; j <= n; j += v){
            a[j-1] ^= 1;
        }
        int cnt = 0;
        for(int j = 0; j < n; j++){
            cnt += a[j];
        }
        // cout << cnt << "\n";
        ans = max(ans, cnt);
    }
    cout << ans << "\n";
    return 0;
}
