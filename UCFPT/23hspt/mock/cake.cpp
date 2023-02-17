#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

map<int, int> memo;

int solve(int k){
    if(memo.find(k) != memo.end()){
        return memo[k];
    }
    memo[k] = 1 + 2 * solve(k / 2);
    return memo[k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int v; cin >> v;
    memo[1] = 0;
    cout << solve(v) << "\n";
}