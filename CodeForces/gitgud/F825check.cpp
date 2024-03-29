#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int N = 8005;
    vi memotimes(N + 1, -1);
    memotimes[0] = 0;
    auto digs = [&](int times) -> int {
        int &cnt = memotimes[times];
        if(cnt != -1) return cnt;
        cnt = 0;
        while(times){times /= 10; cnt++; }
        return cnt;
    };
    rep(len, 1, N){
        pi best = {1e9, -1};
        rep(per, 1, len + 1){
            if(len % per != 0) continue;
            pi nxt = {digs(len / per) + per, per};
            if(nxt.f < best.f){
                if(best.s != -1) cout << len << " " << per << "\n";
                best = nxt;
            }
        }
    }
    
    return 0;
}
