#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(_, 0, nc){
        int cn; ll m; cin >> cn >> m;
        unordered_set<ll> ss;
        ll pre = 0, cur = 1;
        // ss.insert(pre * m + cur);
        while(!ss.count(pre * m + cur)){
            ss.insert(pre * m + cur);
            cur += pre;
            pre = cur - pre;
            if(cur >= m) cur -= m;
        }
        cout << cn << " " << sz(ss) << "\n";
    }
    return 0;
}
