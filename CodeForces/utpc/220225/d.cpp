#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi score(n);
    rep(i, 0, n - 1){
        int j, k; cin >> j >> k;
        j--,k--;
        score[j] += a[k];
        score[k] += a[j];
    }
    int ans = 0;
    rep(i, 0, n) ans = max(ans, score[i] + a[i]);
    cout << ans << "\n";
}