#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

pair<bool, string> calc(queue<int> left, queue<int> right, int x, int t, string cur) {
    while(sz(left) || sz(right)) {
        int distleft = 1e9;
        if(sz(left)) {
            distleft = x - (t + left.front());
        }
        int distright = 1e9;
        if(sz(right)) {
            distright = right.front() - t - x;
        }
        if(min(distleft, distright) < 1) {
            return {false, ""};
        }
        if(sz(cur) && cur.back() == 'L' && distleft == 1) {
            cur += 'D';
            x++;
            t++;
            continue;
        }
        if(cur.back() == 'L') {
            cur += 'R';
            if(sz(right)) right.pop();
        } else {
            cur += 'L';
            if(sz(left)) left.pop();
        }
        t++;
    }
    return {true, cur};
}

void solve() {
    string s; cin >> s;
    int x = 0;
    int n = sz(s);
    rep(i, 0, n) {
        if(s[i] == 'X') {
            x = i;
        }
    }
    queue<int> left, right;
    for(int i = x-1; i >= 0; i--) {
        if(s[i] == '#') left.push(i);
    }
    rep(i, x+1, n) {
        if(s[i] == '#') right.push(i);
    }
    {
        auto lc(left), rc(right);
        if(sz(lc)) lc.pop();
        if(sz(rc)) rc.pop();
        auto [works, ans] = calc(lc, right, x, 1, string("L"));
        if(works){
            cout << "Yes\n";
            cout << ans << "\n";
            return;
        }
        tie(works, ans) = calc(left, rc, x, 1, string("R"));
        if(works){
            cout << "Yes\n";
            cout << ans << "\n";
            return;
        }
        cout << "No\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }

    return 0;
}
