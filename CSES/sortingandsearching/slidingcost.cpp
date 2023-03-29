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

struct ms {
    multiset<int> ms;
    ll sum = 0;
    int size() { return ms.size(); }
    int getLast(){ if(size() == 0){return INT_MIN; }return *ms.rbegin(); }
    int popLast(){
        int v = getLast();
        remove(v);
        return v;
    }
    int getFirst(){ return *ms.begin(); }
    int popFirst(){
        int v = getFirst();
        remove(v);
        return v;
    }
    void insert(int v){
        ms.insert(v);
        sum += v;
    }
    void remove(int v){ ms.erase(ms.find(v)); sum -= v;}
};

void balance(ms &lo, ms &hi){
    while(sz(hi) < sz(lo)){
        int v = lo.popLast();
        hi.insert(v);
    }
    while(sz(lo) <= sz(hi) - 1){
        int v = hi.popFirst();
        lo.insert(v);
    }
}

ll ans(ms &lo, ms &hi){
    balance(lo, hi);
    int median = lo.getLast();
    return (median * sz(lo) - lo.sum) + hi.sum - median * sz(hi);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n,k; cin >> n >> k;
    map<int, int> freq;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    ms lo, hi;
    rep(i, 0, k){
        lo.insert(a[i]);
    }
    cout << ans(lo, hi) << " ";
    rep(i, k, n){
        if(a[i - k] > lo.getLast()){
            hi.remove(a[i - k]);
        }
        else{
            lo.remove(a[i - k]);
        }
        balance(lo, hi);
        if(a[i] > lo.getLast()){
            hi.insert(a[i]);
        }
        else{
            lo.insert(a[i]);
        }
        cout << ans(lo, hi) << " ";
    }
    cout << nL;

    return 0;
}
