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

const int N = 2e5+10;
using bs = bitset<N>;

vector<int> condense(vector<int> items){
    int sum = accumulate(begin(items), end(items), 0);
    vector<int> freq(sum+1);
    for(int i : items) if(i) freq[i]++;
    items.clear();
    for(int i = 0; i <= sum; i++) {
        int amt = (freq[i]-1)/2;
        if(amt) {
            freq[2*i] += amt;
            freq[i] -= 2*amt;
        }
        while(freq[i]) items.push_back(i), freq[i]--;
    }
    return items;
}

vector<int> condense(vector<int> items){
    priority_queue<int,vector<int>,greater<int>> pq;
    for(auto x: items) pq.push(x);
    vector<int> weights;
    while(pq.size() >= 3){
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int c = pq.top(); pq.pop();
        if(a == b && c == b){
            pq.push(a);
            pq.push(a*2);
        }else{
            pq.push(b);
            pq.push(c);
            weights.push_back(a);
        }
    }
    while(pq.size()){
        weights.push_back(pq.top());
        pq.pop();
    }
    return weights;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        k = min(n-k, k); // irrelevant
        vvi child(n);
        vi par(n, -1), depth(n);
        rep(i, 1, n) {
            cin >> par[i]; par[i]--;
            depth[i] = 1 + depth[par[i]];
            child[par[i]].push_back(i);
        }
        int mindepth = n;
        rep(i, 0, n) {
            if(sz(child[i]) == 0) mindepth = min(mindepth, depth[i]);
        }
        vi cnt(mindepth+2);
        rep(i, 0, n) {
            cnt[min(mindepth+1, depth[i])]++;
        }
        // cerr << "k: " << k << endl;
        // cerr << "mindepth: " << mindepth << endl;
        // rep(i, 0, sz(cnt)) cerr << i << " " << cnt[i] << endl;
        int ans = 0;
        bs cur, other;
        rep(i, 0, n+1) other[i] = 1;
        cur[0] = 1;
        int left = n;
        rep(i, 0, mindepth+1) {
            rep(j, left-cnt[i]+1, left+1) other[j] = 0;
            left -= cnt[i];
            cur |= cur << cnt[i];
            bs other2 = other;
            if(left > k) {
                other2 >>= left-k;
            } else other2 <<= k-left;
            // cerr << "i=" << i << " left=" << left << endl; 
            if((cur & other2).any()) {
                ans = max(ans, i+1);
                // cerr << i << " works " << endl;
            }
            // rep(i, 0, 10) cerr << cur[i];
            // cerr << endl;
            // rep(i, 0, 10) cerr << other2[i];
            // cerr << endl;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
