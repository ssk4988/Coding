#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vi a(n), b(m);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, m) cin >> b[i];
    sort(all(a));
    sort(all(b));
    reverse(all(a));
    reverse(all(b));
    int pnt = 0;
    int ans = 0;
    for(int i : b){
        while(pnt < n && a[pnt] > i) pnt++;
        if(pnt < n && a[pnt]<=i){
            ans++;
            pnt++;
        }
    }
    cout << ans << "\n";
    
}
