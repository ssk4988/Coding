#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> names(n);
    vi p(n);
    int MINV = 0, MAXV = 10000;
    int rem = 0, add = 0;
    int sum = 0;
    rep(i, 0, n){
        cin >> names[i] >> p[i];
        p[i] *= 100;
        sum += p[i];
        rem += min(50, p[i]);
        add += min(49, MAXV - p[i]);
    }
    vi lbs(n), ubs(n);
    bool valid = true;
    rep(i, 0, n){
        sum -= p[i];
        rem -= min(50, p[i]);
        add -= min(49, MAXV - p[i]);
        int lb = max(0, p[i] - 50), ub = min(MAXV, p[i] + 49);
        lb = max(lb, MAXV - (sum + add));
        ub = min(ub, MAXV - (sum - rem));
        if(lb > ub){
            valid = false;
        }
        lbs[i] = lb;
        ubs[i] = ub;
        sum += p[i];
        rem += min(50, p[i]);
        add += min(49, MAXV - p[i]);
    }
    if(valid){
        cout << fixed << setprecision(2);
        rep(i, 0, n){
            cout << names[i] << " " << (lbs[i] / 100.0) << " " << (ubs[i] / 100.0) << "\n";
        }
    }
    else{
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}
