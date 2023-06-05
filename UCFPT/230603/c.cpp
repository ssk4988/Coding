#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    vl pref(a);
    rep(i, 1, n){
        pref[i] += pref[i - 1];
    }
    int pnter = n - 1;
    rep(i, 0, k){
        ll v; cin >> v;
        while(pnter >= 0 && a[pnter] > v){
            pnter--;
        }
        ll sum = 0;
        if(pnter >= 0){
            sum += pref[pnter];
        }
        sum += v * (n - 1 - pnter);
        cout << sum << "\n";
    }
    return 0;
}
