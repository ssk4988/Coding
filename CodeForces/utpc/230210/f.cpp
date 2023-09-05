#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int maxn = 4000100;
    vi p(maxn, 1);
    rep(i, 2, maxn){

        if(p[i] == 1) for(int j = i; j < maxn; j += i) if(p[j] == 1) p[j] = i;
    }
    vi fs(maxn), ans(maxn);
    ll res = 0;
    int n; cin >> n;
    rep(i, 2, n + 1){
        int cur = i;
        while(cur != 1){
            fs[i]++;
            cur /= p[cur];
        }
        ans[i] = ans[i - fs[i]] + 1;
        res += ans[i];
        // if(i < 15)cout << i << " " << fs[i] << " " << ans[i] << "\n";
        
    }
    cout << res << "\n";
}
