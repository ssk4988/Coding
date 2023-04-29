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

int n;
// assume no duplicates before
bool bt(map<int, int> &freq){
    if(freq[0] > 1) return false;
    vi moves;
    vi twocnt;
    for(auto &p : freq){
        if(p.s > 2) return false;
        if(p.s == 2) twocnt.pb(p.f);
        if(p.f > 0 && freq[p.f - 1] == 0) moves.pb(p.f);
    }   
    if(sz(twocnt) > 1) return false;
    if(sz(twocnt) == 1){
        moves.clear();
        if(twocnt[0] > 0 && freq[twocnt[0] - 1] == 0) moves.pb(twocnt[0]);
    }
    if(sz(moves) == 0) return false;
    for(int idx : moves){
        freq[idx]--;
        freq[idx - 1]++;
        if(!bt(freq)){
            return true;
        }
        freq[idx - 1]--;
        freq[idx]++;
    }
    return false;
}

bool calcsolve(map<int, int> &freq, vi &state){
    // sort(all(state)
    if(freq[0] > 1) return false;
    vi moves;
    vi twocnt;
    for(auto &p : freq){
        if(p.s > 2) return false;
        if(p.s == 2) twocnt.pb(p.f);
        if(p.f > 0 && freq[p.f - 1] == 0) moves.pb(p.f);
    }   
    if(sz(twocnt) > 1) return false;
    if(sz(twocnt) == 1){
        moves.clear();
        if(twocnt[0] > 0 && freq[twocnt[0] - 1] == 0){
            moves.pb(twocnt[0]);
            // make the move
            freq[twocnt[0]]--;
            freq[twocnt[0] - 1]++;
            rep(i, 0, sz(state)){
                if(state[i] == twocnt[0]){
                    state[i]--;
                    break;
                }
            }
            return !calcsolve(freq, state);
        }
    }
    if(sz(moves) == 0) return false;
    int thisguywins = false;
    rep(i, 0, sz(state)){
        // if(state[i] + 1 < state[i + 1]){
        //     thisguywins = !thisguywins;
        // }
        thisguywins ^= (state[i] - i) % 2;
    }
    return thisguywins;

}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    vi a(n);
    map<int, int> freq;
    rep(i, 0, n){
        cin >> a[i];
        freq[a[i]]++;
    }
    sort(all(a));
    map<int, int> freq2(freq);
    // bool win = bt(freq);
    bool win2 = calcsolve(freq2, a);
    // assert(win == win2);
    // cout << win << " " << win2 << nL;
    cout << (win2 ? "sjfnb" : "cslnb") << nL;
    
    return 0;
}