#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;

vl h;
int n;

bool block(int i, int j, int k){
    // does j block i-k connection
    ll ij = h[j] - h[i];
    ll ik = h[k] - h[i];
    return ij * (k - i) > ik * (j - i);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    h.assign(n, 0);
    rep(i, 0, n){
        cin >> h[i];
    }
    ll curans = 0;
    vector<set<int>> forward(n);
    rep(i, 0, n){
        rep(j, i + 1, n){
            if(forward[i].size() == 0 || !block(i, *(forward[i].rbegin()), j)){
                forward[i].insert(j);
            }
        }
        curans += forward[i].size();
    }
    int q; cin >> q;
    rep(i, 0, q){
        int k, v; cin >> k >> v;
        k--;
        h[k] += v;
        curans -= forward[k].size();
        forward[k].clear();
        rep(j, k + 1, n){
            if(forward[k].size() == 0 || !block(k, *(forward[k].rbegin()), j)){
                forward[k].insert(j);
            }
        }
        curans += forward[k].size();
        rep(j, 0, k){
            auto it = forward[j].begin();
            curans -= forward[j].size();
            while((it = forward[j].upper_bound(k)) != forward[j].end() && block(j, k, *it)){
                forward[j].erase(it);
            }
            auto itl = forward[j].lower_bound(k);
            itl = prev(itl);
            if(!block(j, *itl, k)){
                forward[j].insert(k);
            }


            curans += forward[j].size();
        }
        cout << curans << "\n";
    }
    

    return 0;
}