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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string str; cin >> str;
        vi cnt(2);
        int n = str.length();
        vi st(n);
        rep(i, 0, n){
            st[i] = str[i] - '0';
            cnt[st[i]]++;
        }
        vvi fr(2, vi(2));
        fr[1] = cnt;
        int noswapans = n;
        noswapans = min(cnt[0], cnt[1]);
        rep(i, 0, n){
            fr[0][st[i]]++;
            fr[1][st[i]]--;
            noswapans = min(noswapans, fr[0][1] + fr[1][0]);
        }
        // operations, removals
        pi swapans = {noswapans, noswapans};
        fr = vvi(2, vi(2));
        fr[1] = cnt;
        rep(i, 0, n - 1){
            // swap
            swap(st[i], st[i + 1]);
            fr[0][st[i]]++;
            fr[1][st[i]]--;
            swapans = min(swapans, {fr[0][1] + fr[1][0] + 1, fr[0][1] + fr[1][0]});
            fr[0][st[i]]--;
            fr[1][st[i]]++;
            swap(st[i], st[i+1]);
            fr[0][st[i]]++;
            fr[1][st[i]]--;
        }
        int swapops = swapans.f - swapans.s;
        int remops = swapans.s;
        ll cost = 1'000'000'000'000LL * swapops + 1'000'000'000'001LL * remops;
        cout << cost << nL;
    }
    
    return 0;
}
