#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i,a, b) for(int i = a; i <(b); i++)

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc; 
    set<char> v;
    v.insert('a');
    v.insert('e');
    v.insert('i');
    v.insert('o');
    v.insert('u');
    v.insert('y');
    set<char> c;
    for(char c1 = 'a'; c1 <= 'z'; c1++){
        if(v.count(c1) == 0) c.insert(c1);
    }
    rep(cn, 0, nc){
        string str; cin >> str;
        int n = sz(str);
        vi isv(n), isc(n);
        bool determined = false;
        bool evenc = false, oddc = false, evenv = false, oddv = false;
        rep(i, 0, n){
            if(v.count(str[i])) isv[i] = true;
            if(c.count(str[i])) isc[i] = true;
            if(isv[i] || isc[i]) determined = true;
            if(isv[i]){
                (i % 2 == 0 ? evenv : oddv) = true;
            }
            if(isc[i]){
                (i % 2 == 0 ? evenc : oddc) = true;
            }
        }
        if(evenv && oddv || evenc && oddc || evenv && evenc || oddv && oddc){
            cout << "String #" << (cn + 1) << ": " << "0\n\n";
            continue;
        }
        if(!determined){
            ll res1 = 1, res2 = 1;
            rep(i, 0, n){
                if(i % 2 == 0){
                    res1 *= 6;
                    res2 *= 20;
                }
                else{
                    res1 *= 20;
                    res2 *= 6;
                }
            }
            res1 += res2;
            cout << "String #" << (cn + 1) << ": " << res1 << "\n\n";
            continue;
        }
        bool firstc = false;
        rep(i, 0, n){
            if(isc[i] || isv[i]){
                firstc = (isc[i] ^ (i % 2 == 0));
            }
        }
        ll res = 1;
        rep(i, 0, n){
            if(!isc[i] && !isv[i]){
                res *= ((firstc ^ (i % 2 == 0)) ? 20 : 6);
            }
        }
        cout << "String #" << (cn + 1) << ": " << res << "\n\n";
    }
}
