#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int s, b; cin >> s >> b;
        ll b1 = b;
        int m; cin >> m;
        cout << "Practice #" << (cn + 1) << ": " << s << " " << b << "\n";
        rep(i, 0, m){
            int t; cin >> t;
            while(b1 <= t) b1 *= 2;
            b1 -= t;
            cout << t << " " << b1 << "\n";
        }
        cout << "\n";
    }
}
