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
    int n; cin >> n;
    string str; cin >> str;
    vi best(n); // longest length/2 even palindrome centered right before this index
    int l = -1, r = -1;
    ll ans = 0;
    rep(i, 1, n){
        if(i < r){
            best[i] = min(best[r - i + l], r - i);
        }
        while(i + best[i] < n && i - 1 - best[i] >= 0 && str[i + best[i]] != str[i - 1 - best[i]]) best[i]++;
        if(i + best[i] > r) r = i + best[i], l = i - best[i];
        ans += best[i];
    }
    cout << ans << "\n";

    
    return 0;
}
