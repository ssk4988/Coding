#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int tot = 0;
    rep(i, 0, n){
        ld l, w, d, wei; cin >> l >> w >> d >> wei;
        if(((l <= 56 && w <= 45 && d <= 25) || (l + w + d <= 125)) && wei <= 7){
            tot++;
            cout << 1 << "\n";
        }
        else{
            cout << 0 << "\n";
        }
    }
    cout << tot << "\n";
}