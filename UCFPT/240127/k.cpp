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
    int n; cin >> n;
    int sq = 0;
    while(sq * sq <= n) sq++;
    sq--;
    int ans = 0;
    auto bf = [&](int sum, int used, int sqidx, int lastsq, bool pos, auto &&bf) -> void {
        if(sqidx > sq) return;
        if(used == 4){
            ans += (sum == n && pos);
            return;
        }
        bf(sum, used, sqidx + 1, lastsq, pos, bf);
        bf(sum + (pos ? 1 : -1) * sqidx * sqidx, used + 1, sqidx, sqidx, pos, bf);
        if(lastsq != sqidx){
            bf(sum + (!pos ? 1 : -1) * sqidx * sqidx, used + 1, sqidx, sqidx, !pos, bf);
        }
    };
    bf(0, 0, 0, 0, 1, bf);
    cout << ans << "\n";

    
    return 0;
}
