#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    rep(i, 0, n){
        cout << (i+1) << " " << (i+1) << "\n";
        cout << (i+1) << " " << ((i+1)%n + 1) << "\n";
    }
    k -= 2 * n;
    rep(i, 0, n){
        rep(j, 0, n){
            if(k == 0) break;
            if(i != j && j != (i+1) % n){
                cout << (i+1) << " " << (j+1) << "\n";
                k--;
            }
        }
    }
    return 0;
}
