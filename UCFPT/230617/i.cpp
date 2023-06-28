#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vi cost = {0, 7, 27, 41, 49, 63, 78, 108};
    rep(cn, 0, nc){
        int n; cin >> n;
        int c = 0;
        rep(i, 0, n){
            int k; cin >> k;
            c += cost[k];
        }
        if(c >= 120) c -= 50;
        else if(c >= 89) c -= 30;
        else if(c >= 69) c -= 15;
        cout << c << "\n";
    }
}
