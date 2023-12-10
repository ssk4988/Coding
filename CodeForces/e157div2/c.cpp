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
    vector<string> a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    ll ans = 0;
    map<pi, ll> freq;
    for(auto str : a){
        int sum = 0;
        for(char c : str) sum += c - '0';
        freq[{sz(str), sum}]++;
    }
    for(auto [key, val] : freq){
        ans += val * val;
    }
    // cout << "already " << ans << nL;
    rep(len1, 1, 6){
        rep(len2, 1, 6){
            if((len1 + len2) % 2 != 0) continue;
            int v = (len1 + len2) / 2;
            if(len1 == len2){
                continue;
            }
            else if(len1 < len2){
                int difpref = len2 - v;
                map<int, int> freq1;
                for(auto str : a){
                    if(sz(str) != len2) continue;
                    int dif = 0;
                    rep(i, 0, sz(str)){
                        dif += (i < difpref ? -1 : 1) * (str[i] - '0');
                    }
                    freq1[dif]++;
                }
                for(auto str : a){
                    if(sz(str) != len1) continue;
                    int sum = 0;
                    for(char c : str) sum += c - '0';
                    ans += freq1[sum];
                }
            }
            else{
                map<int, int> freq1;
                for(auto str : a){
                    if(sz(str) != len1) continue;
                    int dif = 0;
                    rep(i, 0, sz(str)){
                        dif += (i < v ? 1 : -1) * (str[i] - '0');
                    }
                    freq1[dif]++;
                }
                for(auto str : a){
                    if(sz(str) != len2) continue;
                    int sum = 0;
                    for(char c : str) sum += c - '0';
                    ans += freq1[sum];
                }
            }
        }
    }
    cout << ans << nL;
    
    return 0;
}
