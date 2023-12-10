#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    int ans = 0;
    priority_queue<int, vi, greater<int>> pq;
    rep(i, 0, n){
        int v;
        if(pq.size() < k){
            v = 0;
        } else {
            v = pq.top(); pq.pop();
        }
        ans += v + a[i];
        pq.push(v + a[i]);
    }
    cout << ans << "\n";
    return 0;
}
