#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;
using ld = long double;

#define pb push_back
#define f first
#define s second
int n, n3;
vpi cs;
using vvi = vector<vi>;
int best = INT_MAX;

int cross(int i, int j){
    return cs[i].f * cs[j].s - cs[i].s * cs[j].f;
}
vvi ss; vi a;
void bt(int idx){
    if(idx == n3){
        int mx = INT_MIN, mn = INT_MAX;
        rep(i, 0, n){
            mx = max(mx, abs(a[i] + cross(ss[i][2], ss[i][0])));
            mn = min(mn, abs(a[i] + cross(ss[i][2], ss[i][0])));
        }
        best = min(best, mx - mn);
        return;
    }
    rep(i, 0, n){
        if(sz(ss[i]) == 3) continue;
        if(sz(ss[i])) a[i] += cross(ss[i].back(), idx);
        ss[i].pb(idx);
        bt(idx + 1);
        ss[i].pop_back();
        if(sz(ss[i])) a[i] -= cross(ss[i].back(), idx);
        if(sz(ss[i]) == 0) break;
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    n3 = n * 3;
    cs.resize(n3);
    rep(i, 0, n3){
        cin >> cs[i].f >> cs[i].s;
    }
    a = vi(n, 0);
    ss.resize(n);
    bt(0);
    cout << fixed << setprecision(1) << ld(best) / 2 << "\n";
}
