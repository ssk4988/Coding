#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int w, h, d; cin >> w >> h >> d;
    if(2 * d >= w || 2 * d >= h){
        cout << 0 << "\n";
    }
    else{
        cout << ((w - 2 * d) * (h - 2 * d)) << "\n";
    }
}
