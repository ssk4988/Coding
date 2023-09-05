#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    const ld PI = acosl(-1);
    const ld EPS = 1e-9;
    rep(cn, 0, nc){
        ld s, r; cin >> s >> r;
        ld ans;
        if(r >= s * sqrtl(2) / 2 - EPS){
            ans = s * s;
        }
        else if(r <= s / 2 + EPS){
            ans = PI * r * r;
        }
        else{
            ld s2 = s / 2;
            ld s1 = sqrtl(r * r - s2 * s2);
            ld rem = PI * r * r * 2 * atan(s1 / s2) / 2 / PI - s2 * s1;
            ans = PI * r * r - 4 * rem;
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
}
