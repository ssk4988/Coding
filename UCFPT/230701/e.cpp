#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

int main() {
    freopen("ghanophobia.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string str; cin >> str;
        int a, b;
        rep(i, 0, sz(str)){
            if(str[i] == ':'){
                a = stoi(str.substr(0, i));
                b = stoi(str.substr(i + 1));
            }
        }
        int e1 = 1, g1 = 6;
        int e2 = a, g2 = b;
        int ans = 0;
        if(e1 + e2 < g1 + g2){
            ans = -1;
        }
        else if(e1 + e2 > g1 + g2){
            ans = 1;
        }
        else{
            e1 *= 2;
            g2 *= 2;
            if(e1 + e2 < g1 + g2){
                ans = -1;
            }
            else if(e1 + e2 > g1 + g2){
                ans = 1;
            }
            else ans = 0;
        }
        cout << "Case " << (cn + 1) << ": ";
        if(ans == -1) cout << "NO";
        else if(ans == 1) cout << "YES";
        else cout << "PENALTIES";
        cout <<"\n";
    }
}
