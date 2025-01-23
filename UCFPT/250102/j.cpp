#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; string first; cin >> n >> first;
        vi p(n);
        int correct = 0;
        rep(i, 0, n){
            cin >> p[i]; p[i]--;
            correct += p[i] == i;
        }
        if(n == 2){
            cout << "Alice\n";
        } else if(n == 3) {
            if(correct == 0){
                cout << (first == "Alice" ? "Bob" : "Alice") << "\n";
            } else if(correct == 1) {
                cout << first << "\n";
            } else assert(false);
        } else {
            cout << (correct == n-2 && first == "Alice" ? "Alice" : "Bob") << "\n";
        }
    }
    return 0;
}
