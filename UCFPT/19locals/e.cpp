#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi composite(5000000);
    vi composite1(5000000);
    rep(i, 2, n+1){
        if(!composite[i]){
            for(int j = i * i; j < sz(composite) ; j += i) composite[j] = true;
        }
    }
    rep(i, 2, sz(composite1)){
        if(!composite1[i] && ll(i) * i < sz(composite1)){
            for(int j = i * i; j < sz(composite1) ; j += i) composite1[j] = true;
        }
    }
    vi res;
    rep(i, 2, sz(composite)){
        if(!composite[i] && composite1[i]) res.push_back(i);
    }
    // cout << sz(res) << endl;
    cout << res[k-1] << "\n";

    return 0;
}
