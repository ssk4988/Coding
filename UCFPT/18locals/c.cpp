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
    vi w(10, true);
    int c; cin >> c;
    rep(i, 0, c){
        int d; cin >> d;
        w[d] = false;
    }
    int ans = 10000;
    int target; cin >> target;
    if(w[0]){
        ans = target;
    }
    rep(i, 1, 1000){
        bool valid = true;
        int j = i;
        while(j){
            int d = j % 10;
            if(!w[d]) valid = false;
            j /= 10;
        }
        if(valid){
            ans = min(ans, abs(i - target));
        }
    }
    cout << ans << "\n";
}
