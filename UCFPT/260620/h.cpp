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
gggggggg
gggggghH
ggggghIH
*/
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int k; cin >> k;
    string s("");
    while(sz(s) < 1000) s += 'g';
    k--;
    cout << s << "\n";
    for(int i = sz(s)-1; i > 0 && k; i--) {
        k--;
        s[i] -= 31;
        s[i-1]++;
        cout << s << "\n";
    }


    return 0;
}
