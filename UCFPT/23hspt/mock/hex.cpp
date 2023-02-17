#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, s;
    cin >> n >> s;
    vector<string> strs(n);
    rep(i, 0, n){
        cin >> strs[i];
    }
    string target; cin >> target;
    bool works = false;
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == j) continue;
            string strcb = strs[i] + strs[j];
            rep(k, 0, sz(strcb) + 1 - s){
                if(strcb.substr(k, s) == target){
                    works = true;
                }
            }
        }
        if(strs[i] == target) works = true;
    }
    cout << (works ? "Helga is loveable" : "Toil and Trouble") << "\n";
}