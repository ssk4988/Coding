#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

/*
n * m

reat
eate

reate
reat|e
rea|te
re|ate
r|eate


pee
e
pe
pee
peee

pe
p|e
pe|

its related to counting overlaps

exclude 1 when overlap is entire string

when find a match of length l, subtract l+1 from answer. 

abc
abc

aabc
abc
ac
ababc
abbc
abc dup
abcabc
abcbc
abcc


eee eeee
6
n * m gives 12
ee
eee
eeee
eeeee
eeeeee
eeeeeee
*/

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string a, b; cin >> a >> b;
    int n = sz(a), m = sz(b);
    ll ans = m;
    vi freq(26);
    rep(i, 0, m-1) freq[b[i]-'a']++;
    rep(i, 1, n) ans += m-freq[a[i]-'a'];
    cout << ans << "\n";

    return 0;
}
