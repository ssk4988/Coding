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

const int DIF = 1e5;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll w; cin >> w;
    vl left(8), used(8);
    rep(i, 0, 8) cin >> left[i];
    ll best = 0;
    const int WIDTH = 8 * (8 * 9 / 2) + 1;
    for(int i = 7; i >= 0; i--){
        ll add = min(left[i], (w - best) / (i+1));
        left[i] -= add;
        used[i] += add;
        best += (i+1) * add;
    }
    const ll ref = best;
    const ll refidx = WIDTH / 2;
    const ll widx = w - ref + refidx;
    bitset<WIDTH> bs;
    bs[refidx] = true;
    rep(idx, 0, 7){
        rep(i, 0, min(8LL, used[idx])){
            bs |= bs >> (idx+1);
        }
        rep(i, 0, min(8LL, left[idx])){
            bs |= bs << (idx+1);
        }
    }
    rep(i, 0, WIDTH){
        if(bs[i]){
            if(i < widx){
                ll add = min((widx - i) / 8, left[7]);
                best = max(best, i + 8 * add - refidx + ref);
            }
            else{
                ll sub = min(used[7], (i - widx + 8 - 1) / 8);
                if(i - 8 * sub <= widx)
                    best = max(best, i - 8 * sub - refidx + ref);
            }
        }
    }
    cout << best << "\n";
    
    
    return 0;
}