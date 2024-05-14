#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    string str;
    cin >> str;
    string fr = str.substr(0, n / 2), ba = str.substr(n - n / 2);
    reverse(all(ba));
    str.clear();
    rep(i, 0, sz(fr)){
        str += fr[i];
        str += ba[i];
    }
    n = sz(str);
    vi best(n); // longest length/2 even palindrome centered right before this index
    int l = -1, r = -1;
    int ans = 0;
    set<int> pl1; // set of i such that [0...i) is even length palindrome
    pl1.insert(0);
    rep(i, 1, n){
        if(i < r){
            best[i] = min(best[r - i + l], r - i);
        }
        while(i + best[i] < n && i - 1 - best[i] >= 0 && str[i + best[i]] == str[i - 1 - best[i]]) best[i]++;
        if(i + best[i] > r) r = i + best[i], l = i - best[i];
        auto it = pl1.lower_bound(i - best[i]);
        if(it != pl1.end()){
            ans = max(ans, i + i - *it);
        }
        if(i - best[i] == 0) pl1.insert(i + best[i]);
    }
    cout << ans/2 << "\n";
    
    return 0;
}
