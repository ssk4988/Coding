#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vi to(int a, int b, int k) {
    vi res{a};
    if(a == b) {
        rep(i, 0, k){
            if(i & 1) res.pb(a);
            else res.pb(a * 2);
        }
        return res;
    }
    // a < b
    int ap = __lg(a), bp = __lg(b);
    vi res1{b};
    int a1 = a, b1 = b;

    while(a1){
        a1 >>= 1;
        res.pb(a1);
    }
    while(b1) {
        b1 >>= 1;
        res1.pb(b1);
    }
    // if(sz(res) + sz(res1) - 1 - 1 <= k){
    //     res.pop_back();
    //     while(sz(res) + sz(res1) - 1 < k) res.pb(0);
    //     return res;
    // }
    while(min(sz(res), sz(res1)) >= 2 && res[sz(res)-2] == res1[sz(res1)-2]){
        res.pop_back();
        res1.pop_back();
    }
    res.pop_back();
    if((sz(res) + sz(res1) - 1) % 2 != k % 2 || (sz(res) + sz(res1) - 1) > k) return {};
    while(sz(res) + sz(res1) - 1 < k){
        int v = res1.back();
        if(v > 1)res1.pb(v/2);
        else res1.pb(v*2);
        res1.pb(v);
    }
    reverse(all(res1));
    res.insert(res.end(), all(res1));
    assert(sz(res) == k + 1);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        // if(cn > 0) continue;
        if(a == vi(n, -1)){
            rep(i, 0, n){
                if(i & 1) a[i] = 1;
                else a[i] = 2;
            }
        }
        rep(i, 0, n){
            if(a[i] != -1){
                for(int j = i-1; j >= 0; j--){
                    if(a[j+1] > 1) a[j] = a[j+1]/2;
                    else a[j] = a[j+1]*2;
                }
                break;
            }
        }
        for(int i = n-1; i >= 0; i--){
            if(a[i] != -1){
                rep(j, i+1, n){
                    if(a[j-1] > 1) a[j] = a[j-1]/2;
                    else a[j] = a[j-1]*2;
                }
                break;
            }
        }
        bool found = true;
        rep(i, 0, n){
            if(a[i] == -1) continue;
            rep(j, i+1, n){
                if(a[j] == -1) continue;
                vi inter = to(min(a[i], a[j]), max(a[i], a[j]), j - i);
                if(sz(inter) == 0){
                    found = false;
                    goto done;
                } else {
                    if(a[j] < a[i]) reverse(all(inter));
                    rep(k, 0, sz(inter)){
                        a[i+k] = inter[k];
                    }
                    // goto done;
                }
                i = j-1;
                break;
            }
        }
        done:
        if(!found) cout << -1 << "\n";
        else{
            rep(i, 0, n) cout << a[i] << " ";
            cout << "\n";
        }
    }
    
    return 0;
}
