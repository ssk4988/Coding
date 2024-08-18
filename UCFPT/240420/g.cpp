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

vi bases = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
vector<string> bs = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "C",
    "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", "M"};

string roman(int v){
    string res = "";
    while(v){
        for(int i = sz(bases) - 1; i >= 0; i--){
            if(bases[i] <= v){
                v -= bases[i];
                res += bs[i];
                break;
            }
        }
    }
    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    assert(sz(bs) == sz(bases));

    vector<pair<string, int>> order;
    rep(i, 1, 1001){
        order.push_back({roman(i), i});
    }
    sort(all(order));
    int mindex = 0;

    rep(i,0, sz(order)){
        if(order[i].second == 1000) mindex = i;
    }
    // cout << sz(order) << " " << mindex << "\n";
    vi fron(1001), bac(1001);
    rep(i, 0, sz(order)){
        fron[order[i].second] = i;
        bac[order[i].second] = sz(order) - 1 - i;
    }
    // cout << fron[1000] << " " << bac[1000] << "\n";
    int n; cin >> n;
    // vector<pair<string, int>> stuff;
    rep(i, 0, n){
        int v; cin >> v;
        ll fans = 0, bans = 0;
        while(v > 1000){
            // cout << " did iter " << v << " " << fans << " " << bans << "\n";
            fans += fron[1000] + 1;
            bans += bac[1000];
            v -= 1000;
        }
        // cout << "cur at " << v << " " << fans << " " << bans << "\n";
        // cout << v << " val " << fron[v] << " " << bac[v] << "\n";
        fans += fron[v];
        bans += bac[v];
        if(fron[v] <= fron[1000]){
            cout << (fans + 1) << "\n";
        }
        else{
            cout << -(bans + 1) << "\n";
        }
    }


    return 0;
}