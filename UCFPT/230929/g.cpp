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

string nextstr(string &p){
    vi freq(10);
    for(char c : p){
        freq[c - '0']++;
    }
    string res; 
    rep(i, 0, 10){
        if(freq[i] == 0) continue;
        int v = freq[i];
        vi digs;
        while(v > 0){
            digs.pb(v % 10); v /= 10;
        }
        reverse(all(digs));
        for(int d : digs) res.pb('0' + d);
        res.pb('0' + i);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string start, target; cin >> start >> target;
    set<string> found;
    found.insert(start);
    int times = 0;
    for(int i = 0; i < 105 && !found.count(target); i++){
        start = nextstr(start);
        found.insert(start);
    }
    if(sz(found) > 100){
        cout << "I'm bored\n";
    }
    else if(!found.count(target)){
        cout << "Does not appear\n";
    }
    else{
        cout << sz(found) << "\n";
    }
}
