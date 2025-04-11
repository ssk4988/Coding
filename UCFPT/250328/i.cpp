#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    if(t == 5) {
        cout << "PLAY" << endl;
        cout << "SKIP" << endl;
        cout << "SKIP" << endl;
        cout << "PLAY" << endl;
        cout << "SKIP" << endl;
        return 0;
    }
    while(true) {
        string r;
        int amt, b; cin >> r;
        if(r == "WIN" || r == "LOSE"){
            return 0;
        }
        cin >> amt >> b;
        if(b * 3 < amt) {
            cout << "PLAY" << endl;
        } else {
            cout << "SKIP" << endl;
        }
    }

    return 0;
}
