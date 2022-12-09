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
    string k;
    ll score = 0;
    while((cin >> k) && k.length() > 1){
        set<char> set;
        rep(i, 0, k.length() / 2){
            set.insert(k[i]);
        }
        rep(i, k.length() / 2, k.length()){
            if(set.find(k[i]) != set.end()){
                if('a' <= k[i] && k[i] <= 'z'){
                    score += 1 + k[i] - 'a';
                }
                else{
                    score += 1 + k[i] - 'A' + 26;
                }
                break;
            }
        }
    }
    cout << score << nL;
    
    return 0;
}