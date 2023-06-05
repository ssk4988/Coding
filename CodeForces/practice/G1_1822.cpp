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
using vvl = vector<vl>;

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


bool DEBUG = true;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    int LIM = 1e6 + 10;
    vvi fs(LIM);
    rep(i, 1, LIM)
    {
        for (int j = i; j < LIM; j += i)
        {
            fs[j].pb(i);
        }
    }
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi a(n);
        unordered_map<int, unordered_map<int, ll>> freq1;
        int maxv = 0;
        rep(i, 0, n)
        {
            cin >> a[i];
            maxv = max(maxv, a[i]);
        }
        maxv++;
        unordered_map<int, int> freq;
        ll ans = 0;
        rep(i, 0, n)
        {
            freq[a[i]]++;
        }
        for(auto &p : freq){
            auto [i, f] = p;
            for(int j : fs[i]){
                if((i / j) % j != 0) continue;
                if(j == 1){
                    if(freq[i] > 2){
                        ans += ll(freq[i]) * (freq[i] - 1) * (freq[i] - 2);
                    }
                }
                else if(freq.count(i / j) && freq.count(i / j / j)){
                    ans += ll(freq[i]) * freq[i / j] * freq[i / j / j];
                }
            }
        }
        cout << ans << nL;
    }

    return 0;
}
