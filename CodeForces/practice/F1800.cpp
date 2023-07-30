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
    map<vi, int> hs;
    auto has = [](vi k)->int{
        return k[0] | (k[1] << 26) | (k[2] << 27);
    };
    unordered_map<int, int> freq;
    ll ans = 0;
    int a = 1 << 26;a--;
    rep(i, 0, n){
        string str; cin >> str;
        int f = 0;
        vi fq(26);
        rep(j, 0, sz(str)){
            f ^= 1 << (str[j] - 'a');
            fq[str[j] - 'a']++;
        }
        int other = a ^ f;
        rep(j, 0, 26){
            if((other & (1 << j)) && fq[j] == 0){
                vi k = {other ^ (1 << j), (1 - (sz(str) % 2)), j};
                // if(hs.count(k) == 0) hs[k] = sz(hs);
                ans += freq[has(k)];
            }
        }
        rep(j, 0, 26){
            if(fq[j] == 0){
                vi k = {f, sz(str) % 2, j};
                // if(hs.count(k) == 0) hs[k] = sz(hs);
                freq[has(k)]++;

            }
        }
    }
    cout << ans << nL;
    
    return 0;
}