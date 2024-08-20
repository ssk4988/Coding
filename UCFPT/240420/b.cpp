#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x)(int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const int MAX_M = 200000005;
bool used[MAX_M];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a, m; cin >> a >> m;
    int cnt = 1;
    if(a == m){
        cout << 1 << "\n";
        return 0;
    }
    vector<ll> seq = {a};
    used[a] = true;
    int cursmallest = 1;
    while(!used[m]){
        while(used[cursmallest]) cursmallest++;
        seq.push_back(seq.back() + cursmallest);
        if(seq.back() < MAX_M) used[seq.back()] = true;
        for(int i = sz(seq) - 2; i >= 0; i--){
            if(seq.back() - seq[i] < MAX_M){
                used[seq.back() - seq[i]] = true;
            }
            else break;
        }
    }
    cout << sz(seq) << "\n";


    return 0;
}