#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using ull = uint64_t;

struct H{
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) {return x + o.x + (x + o.x < x);}
    H operator-(H o) {return *this + ~o.x;}
    H operator*(H o) {auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
    ull get() const {return x + !~x; }
    bool operator == (H o) const {return get() == o.get();}
    bool operator <(H o) const {return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<H> pws;
    const int maxn = 2e6+ 100;
    pws.pb(1);
    rep(i, 0, maxn){
        pws.pb(pws.back() * C);
    }
    string str; cin >> str;
    vector<H> prefs, ip;
    rep(i, 0, n){
        prefs.pb(H(i ? prefs.back() : 0) + pws[i] * H(str[i] - 'A' + 1));
        ip.pb(pws[i] * H(str[i] - 'A' + 1));
    }
    if(n % 2 != 1 || n == 1){
        cout << "NOT POSSIBLE\n";
        return 0;
    }
    vi works;
    rep(i, 1, n - 1){
        H pref = prefs[i - 1];
        H suff = prefs[n - 1] - prefs[i];
        H res = pref * pws[1] + suff;
        int en = (n / 2 - 1 >= i) + n/2 - 1;
        if(n /2 - 1 >= i){
            // split
            H split1 = prefs[i - 1];
            H split2 = prefs[n/2 - 1 + 1] - prefs[i];
            H split3 = split1 * pws[1] + split2;
            H res2 = split3 + split3 * pws[n/2];
            if(res2 == res)works.pb(i);
        }
        else{
            // same
            H first = prefs[n/2 - 1];
            H second = first * pws[n/2];
            H res2 = (first + second) * pws[1];
            if(res2 == res)works.pb(i);
        }
    }
    //i == 0
    {
        H res = prefs[n - 1] - prefs[0];
        H split1 = prefs[n/2 - 1 + 1] - prefs[0];
        H res2 = split1 + split1 * pws[n/2];
        if(res2 == res) works.pb(0);
    }
    // i == n - 1
    if(n > 1)
    {
        H res = prefs[n - 2];
        H split1 = prefs[n/2-1];
        H res2 = split1 + split1 * pws[n/2];
        if(res2 == res) works.pb(n - 1);
    }
    if(works.size() == 0){
        cout << "NOT POSSIBLE\n";
    }
    else{
        set<H> hs;
        for(int i : works){
            H split3;
            if(i == 0){
                split3 = prefs[n/2] - prefs[0];
            }
            else if(n /2 - 1 >= i){
                // split
                H split1 = prefs[i - 1];
                H split2 = prefs[n/2 - 1 + 1] - prefs[i];
                split3 = split1 * pws[1] + split2;
            }
            else{
                // same
                split3 = prefs[n/2 - 1] * pws[1];
            }
            hs.insert(split3);
        }
        if(sz(hs) == 1){
            for(int i : works){
                H split3;
                if(n /2 - 1 >= i){
                    // split
                    H split1 = prefs[i - 1];
                    H split2 = prefs[n/2 - 1 + 1] - prefs[i];
                    split3 = split1 * pws[1] + split2;
                }
                else{
                    // same
                    split3 = prefs[n/2 - 1] * pws[1];
                }
                if(split3 == *(hs.begin())){
                    string res;
                    rep(j, 0, n){
                        if(j == i) continue;
                        res.pb(str[j]);
                        if(sz(res) == n/2) break;
                    }
                    cout << res << "\n";
                    break;
                }
            }
        }
        else{
            cout << "NOT UNIQUE\n";
        }
        int i = works[0];
        
    }
    return 0;
}
