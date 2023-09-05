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
    vi cnt(10);
    rep(i, 1, 1000){
        int v = i;
        while(v){
            cnt[v % 10]++;
            v /= 10;
        }
        rep(j, 1, 9) assert(cnt[j] >= cnt[j + 1]);
        // if(cnt[0] > cnt[1]) cout << i << " " << cnt[0] << " " << cnt[1] << nL;
    }
    // cout << cnt[1] << nL;
    vl score = {0};
    int startdig = 0;
    ll n; cin >> n;
    ll placevalue = 1;
    for(; score.back() <= n; startdig++){
        score.pb(placevalue + 10 * score.back());
        placevalue *= 10;
    }
    startdig--;
    placevalue /= 10;
    // cout << startdig << " " << placevalue << nL;
    ll ans = 0;
    ll ones = 0;
    while(startdig >= 0){
        int duse = -1;
        ll drem = -1;
        rep(d, 0, 10){
            ll rem = d * placevalue * ones + d * score[startdig];
            if(d > 1){
                rem += placevalue; // a bunch of ones in this place
            }
            if(rem <= n){
                drem = rem;
                duse = d;
            }
        }
        if(duse == 1) ones++;
        n -= drem;
        ans *= 10;
        ans += duse;
        // cout << "using " << duse << " at digit " << startdig << " to remove " << drem << " ones\n";
        startdig--;
        placevalue /= 10;
    }
    ans--;
    cout << ans << nL;
    return 0;
}
