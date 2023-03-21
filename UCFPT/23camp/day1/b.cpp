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
    int sum = 0;
    map<int, int> freq, freq1;
    rep(i, 0, n){
        int v; cin >> v;
        freq[v]++;
        sum += v;
    }
    int sub = 0;
    rep(i, 1, 101){
        if(freq[i] == 0) continue;
        vi facts;
        rep(j, 1, i + 1){
            if(i % j == 0) facts.pb(j);
        }
        rep(j, 1, 101){
            if(freq[j] == 0) continue;
            for(int k : facts){
                sub = max(sub, i + j - i / k - j * k);
            }
        }
    }
    cout << sum - sub << nL;
    
    return 0;
}
