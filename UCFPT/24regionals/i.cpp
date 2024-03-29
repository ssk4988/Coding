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
    int n, m, s, p, q; cin >> n >> m >> s >> p >> q;
    s--;
    vi has(n), want(n);
    rep(i, 0, p){
        int x; cin >> x; x--;
        has[x] = true;
    }
    rep(i, 0, q){
        int x; cin >> x; x--;
        want[x] = true;
    }
    int pages = (n + m - 1) / m;
    int ans = 0;
    int firstdiff = -1, lastdiff = -1;
    rep(i, 0, pages){
        int len = min(m, n - (i * m));
        int diff = 0, on = 0;
        rep(j, 0, len){
            if(has[i * m + j] != want[i * m + j]){
                diff++;
                firstdiff = (firstdiff == -1 ? i : firstdiff);
                lastdiff = i;
            }
            on += want[i * m + j];
        }
        ans += min({diff, 1 + on, 1 + (len - on)});
    }
    if(firstdiff != -1){
        ans += abs(lastdiff - firstdiff) + min(abs(firstdiff - s), abs(lastdiff - s));
    }
    cout << ans << "\n";

    
    return 0;
}
