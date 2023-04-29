#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int ans = n;
    vi tows;
    rep(i, 0, n){
        int k; cin >> k;
        tows.push_back(k);
    }
    sort(all(tows));
    rep(i, 0, n){
        ans = min(ans, tows[i] + (n - 1 - i));
    }
    cout << ans << "\n";

    return 0;
}