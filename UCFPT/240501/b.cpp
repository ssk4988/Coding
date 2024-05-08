#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const int LIM = 1e5 + 600;
int pos[LIM], neg[LIM];

set<int> t[4];

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    auto add = [&](int b) -> void {
        // assume pos and neg have 1 in them
        int m = (pos[b] << 1) ^ neg[b];
        t[m].insert(b);
    };
    auto rem = [&](int b) -> void {
        // assume pos and neg have 1 in them
        int m = (pos[b] << 1) ^ neg[b];
        t[m].erase(b);
    };

    int n; cin >> n;
    vi a(n);
    rep(i, 0, LIM){
        add(i);
    }
    rep(i,0,n){
        cin >> a[i];
        int cur = i;
        rem(cur);
        if(a[i] > 0) pos[cur] += a[i];
        if(a[i] < 0) neg[cur] += abs(a[i]);
        while(true){
            bool did = false;
            if(pos[cur] > 1){
                if(!did) rem(cur+1);
                did = true;
                pos[cur+1] += pos[cur] / 2;
                pos[cur] %= 2;
            }
            if(neg[cur] > 1){
                if(!did) rem(cur+1);
                did = true;
                neg[cur+1] += neg[cur] / 2;
                neg[cur] %= 2;
            }
            add(cur);
            cur++;
            if(!did) break;
        }
        if(sz(t[1]) || sz(t[2])){
            int bestpos = sz(t[2]) ? *t[2].rbegin() : -1;
            int bestneg = sz(t[1]) ? *t[1].rbegin() : -1;
            cout << (bestpos > bestneg ? '+' : '-');

        } else cout << 0;
    }
    cout << "\n";
    
    

    return 0;
}
