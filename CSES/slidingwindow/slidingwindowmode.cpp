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
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    map<int, int> freq;
    int distinct = 0;
    multiset<pii> freqs;
    rep(i, 0, n) {
        freqs.insert({0, -a[i]});
    }
    rep(i, 0, n) {
        freqs.erase(freqs.find({freq[a[i]], -a[i]}));
        freq[a[i]]++;
        freqs.insert({freq[a[i]], -a[i]});
        if(i >= k) {
            freqs.erase(freqs.find({freq[a[i-k]], -a[i-k]}));
            freq[a[i-k]]--;
            freqs.insert({freq[a[i-k]], -a[i-k]});
        }
        if(i >= k-1) cout << -rbegin(freqs)->s << " ";
    }    
    cout << "\n";

    
    return 0;
}
