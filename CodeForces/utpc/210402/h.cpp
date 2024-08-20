#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
const int N = 1e5 + 10;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vvi divs(N);
    rep(i, 2, N){
        for(int j = i; j < N; j += i) divs[j].push_back(i);
    }
    int n; cin >> n;
    vi dp(N);
    rep(i, 0, n){
        int p; cin >> p;
        int best = 1;
        for(int d : divs[p]){
            best = max(best, 1 + dp[d]);
            // cout << p << " " << d << "\n";
        }
        for(int d : divs[p]){
            dp[d] = max(dp[d], best);
        }
    }
    if(n == 1){
        cout << "1\n";
        return 0;
    }
    cout << *max_element(all(dp)) << "\n";

    return 0;
}