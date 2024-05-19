#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;
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

ld eps = 1e-9;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int cn = 1;
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vi order(n);
        iota(all(order), 0);
        vpi a(n);
        rep(i, 0, n) {
            cin >> a[i].f >> a[i].s;
        }
        ld best = 0;
        do {
            ld ans = 0;
            ld dif = 1 << 15;
            rep(_, 0, 50) {
                ld cur = ans + dif;
                ld t = a[order[0]].first;
                bool works = true;
                rep(i, 1, n){
                    t = max(t + cur, ld(a[order[i]].first));
                    if(t > a[order[i]].second + eps) {
                        works = false;
                        break;
                    }
                }
                if(works) ans = cur;
                dif /= 2;
            }
            best = max(best, ans);
        } while (next_permutation(all(order)));
        best *= 60;
        int time = round(best);
        // cout << best << "\n";
        string mstr = to_string(time % 60);
        while(sz(mstr) < 2) mstr = "0" + mstr;
        cout << "Case " << cn++ << ": " << (time / 60) << ":" << mstr << "\n";
    }
    
    return 0;
}
