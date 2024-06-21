#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O2")

using ll = unsigned long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;


#define rep(i,a,b) for(int i =a; i < (b); i++)
#define sz(x)(int)x.size()
#define all(x) begin(x), end(x)

vi primes;
unordered_map<ll, ll> ans;
const ll LIM = 1ULL << 63;
void bt(int pidx, int lim, int used, ll prod, ll ways) {
    if (prod > 1) {
        if(!ans.count(ways)) ans[ways] = prod;
        else ans[ways] = min(ans[ways], prod);
    }
    if(lim == 0) return;
    rep(pw, 1, lim+1){
        __int128_t w = ways;
        __int128_t p = prod;
        p *= primes[pidx];
        w = w * (used + pw) / pw;
        if(max(p, w) >= LIM) break;
        prod = p;
        ways = w;
        bt(pidx+1, pw, used+pw, prod, ways);
    }
}


int main(){
    cin.tie(0)->sync_with_stdio(0);
    rep(i, 2, 1000){
        bool works = true;
        rep(j, 2, i){
            if(i % j == 0) {works = false; break;}
        }
        if(works) primes.push_back(i);
    }
    bt(0, 100, 0, 1, 1);
    ll n;
    while(cin >> n){
        cout << n << " " << ans[n] << "\n";
    }


    return 0;
}
