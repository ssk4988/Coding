#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a, b, n; cin >> a >> b >> n;
    int pa = a, pb = b;
    int ans = 0;
    while(!(pa == n && pb == n)){
        if(pa != pb) pa = pb;
        else pb = min(pb + b - a, n);
        ans++;
    }
    cout << ans << "\n";
    return 0;
}
