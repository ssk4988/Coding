#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = long double;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int w, b, d, s;
        cin >> w >> b >> d >> s;
        int n; cin >> n;
        ld wedgeangle = 2 * acosl(-1) / w;
        int score = 0;
        rep(i, 0, n){
            ld x, y; cin >> x >> y;
            if(x * x + y * y <= b * b){
                // cout << 50 << "\n";
                score += 50;
                continue;
            }
            if(x * x + y * y > s * s)continue;
            int mult = 1;
            if(x * x + y * y <= d * d){
                mult = 2;
            }
            ld x1 = x, y1 = y;
            ld angle = atan2(y1, x1);
            while(angle < 0) angle += 2 * acosl(-1);
            int rat = angle / wedgeangle;
            rat++;
            score += rat * mult;
            // cout << rat * mult << "\n";
        }
        cout << score << "\n";
    }
}
