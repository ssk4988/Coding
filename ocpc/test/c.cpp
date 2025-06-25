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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi res;
    rep(i, 0, 2) {
        string s; cin >> s;
        vi f(26);
        for(char c : s) f[c-'a']++;
        res.push_back(*max_element(all(f)));
    }
    cout << ((res[0] > res[1]) ? "Corrupted Odyssey" : "Random Gibberish") << "\n";
    cout << ((res[0] < res[1]) ? "Corrupted Odyssey" : "Random Gibberish") << "\n";


    return 0;
}
