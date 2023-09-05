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
        int d, n; cin >> d >> n;
        cout << "Grid #" << (cn + 1) << ": ";
        if(d <= (n - 1) * (n - 1) + 1){
            cout << (d * (n - 1) * 2);
        }
        else cout << "impossible";
        cout << "\n\n";
    }
}
