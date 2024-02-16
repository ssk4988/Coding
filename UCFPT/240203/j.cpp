#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll julia; cin >> julia;
    n--;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    reverse(all(a));
    // sz(a) >= 2
    assert(sz(a) >= 2);
    ll ans = a[0] - a[1];
    rep(i, 1, n){
        a[i] += ans;
    }
    ll nummax = 1;
    ll top = a[0];
    rep(i, 1, n){
        if(a[i] == a[0]) nummax++;
    }
    ll inc = 0;
    while(top <= julia){
        ll cyclelen = __lg(nummax) + 1;
        ll dif = nummax == n ? 1e18 : a[nummax - 1] - a[nummax];
        if(dif == 0) {
            nummax++;
            continue;
        }
        assert(dif > 0);
        ll cyclestodo = dif;
        cyclestodo = min(cyclestodo, (julia - top) / (cyclelen - 1));
        if(cyclestodo <= 0) break;
        inc += cyclelen * cyclestodo;
        top += cyclestodo * (cyclelen - 1);
        if(nummax < n) nummax++;
    }
    ans += inc;
    rep(i, 0, nummax){
        a[i] = top;
    }
    rep(i, nummax, n){
        a[i] += inc;
    }
    while(a[0] <= julia){
        nummax = 0;
        rep(i, 0, n){
            if(a[i] == a[0]) nummax++;
            else break;
        }
        rep(i, 0, nummax / 2){
            a[i]++;
        }
        rep(i, nummax, n) a[i]++;
        ans++;
    }
    ans--;
    cout << ans << "\n";


    return 0;
}