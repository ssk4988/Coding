#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = long double;
using vvi = vector<vi>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define pb push_back
#define f first
#define s second

#pragma GCC optimize("Ofast")
#pragma GCC target ("avx2")

const ll lim = 1e15;
// vi primes;
const int psize = 31;
const ll primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127};
ll b;
ll ans;
int plim;
void bt(int idx, ll cur, int used){
    // cout << idx << " "<< cur << " " << used << "\n";
    if(cur > b) return;
    // if(cur > 1){
        // combs[idx].pb(cur * (used % 2 ? 1 : -1));
        ans += (used % 2 ? 1 : -1) * (b / cur);
    // }
    rep(i, idx + 1, plim){
        bt(i, cur * primes[i], used + 1);
    }
}


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int a; cin >> a >> b;
        ans = 0;
        plim = 0;
        while(plim < psize && primes[plim] <= a) plim++;
        bt(-1, 1, 0);
        ans += b;
        cout << ans << "\n";
    }
}
