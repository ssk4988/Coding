#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

// const int bits = 4;

map<pi, int> solve(const int bits){
    vector<set<int>> aset(1 << bits), bset(1 << bits);
    rep(i, 0, 1 << bits){
        rep(j, 0, 1 << bits){
            if((i | j) != (1 << bits) - 1) continue;
            aset[i].insert(j);
            bset[j].insert(i);
        }
    }
    map<pi, int> ans;
    vi solveda(1 << bits), solvedb(1 << bits);
    rep(moves, 0, 10){
        if(moves % 2 == 0){
            vi solves;
            rep(i, 0, 1 << bits){
                if(solveda[i] || sz(aset[i]) == 0) continue;
                if(sz(aset[i]) == 1 || i < *aset[i].begin() || i > *aset[i].rbegin()){
                    solveda[i] = true;
                    solves.pb(i);
                    for(int j : aset[i]){
                        ans[{i,j}] = moves + 1;
                    }
                }
            }
            for(int i : solves){
                rep(j, 0, 1 << bits) bset[j].erase(i);
            }
        }
        else{
            vi solves;
            rep(i, 0, 1 << bits){
                if(solvedb[i] || sz(bset[i]) == 0) continue;
                if(sz(bset[i]) == 1 || i < *bset[i].begin() || i > *bset[i].rbegin()){
                    solvedb[i] = true;
                    solves.pb(i);
                    for(int j : bset[i]){
                        ans[{j,i}] = moves + 1;
                    }
                }
            }
            for(int i : solves){
                rep(j, 0, 1 << bits) aset[j].erase(i);
            }
        }
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int bitlim = 8;
    vector<map<pi, int>> ans(bitlim);
    rep(i, 1, bitlim){
        ans[i] = solve(i);
    }
    // map<pi, int> ans3 = solve(3), ans4 = solve(4);
    // const int bits = 4;
    auto getstr = [&](int v, int s = 4)->string{
        string res;
        rep(i, 0, s){
            res.pb('0' + v % 2);
            v /= 2;
        }
        reverse(all(res));
        return res;
    };
    rep(b, 2, bitlim){
        for(auto [key, val] : ans[b]){
            auto [i,j] = key;
            // if(val <= 2 && (i >= 1 << (bits-1)) && (j >= 1 << (bits-1))){
            //     cout << getstr(i) << "," << getstr(j) << " " << val << " interesting" << nL;
            // }
            // if(val <= 2 && ((i < (1 << (b-1))) || (j < (1 << (b-1))))) continue;
            int i1 = i / 2, j1 = j / 2;
            int prevval = ans[b-1][{i1,j1}];
            if(prevval == val) continue;
            cout << getstr(i,b) << "," << getstr(j,b) << " " << val << " from " << getstr(i1, b-1) << " " << getstr(j1, b-1) << " " << prevval << (val > prevval ? " growth" : "") << nL;
        }

    }
    
    return 0;
}