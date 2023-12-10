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

struct cmp1 {
    bool operator()(const pl a, const pl b)const{
        if(a.f == b.f) return a.s < b.s;
        return a.f < b.f;
    }
};
struct cmp2 {
    bool operator()(const pl a, const pl b)const{
        if(a.s == b.s) return a.f < b.f;
        return a.s < b.s;
    }
};
struct cmp3 {
    bool operator()(const pl a, const pl b)const{
        if(a.f - a.s == b.f - b.s) return a.f < b.f;
        return a.f - a.s < b.f - b.s;
    }
};


int main()
{
    multiset<pl, cmp1> a1;
    multiset<pl, cmp1> c1;
    multiset<pl, cmp2> b2;
    multiset<pl, cmp2> c2;
    multiset<pl, cmp3> a3;
    multiset<pl, cmp3> b3;
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a, b, n; cin >> a >> b >> n;
    rep(i, 0, n){
        pl d; cin >> d.f >> d.s;
        if(i < a){
            a1.insert(d), a3.insert(d);
        }
        else if(i < a + b){
            b2.insert(d), b3.insert(d);
        }
        else{
            c1.insert(d), c2.insert(d);
        }
    }
    int c = n - a - b;
    // cout << "got here" << endl;
    // cout << "in a1:" << endl;
    // for(auto x : a1){
    //     cout << x.f << " " << x.s << endl;
    // }
    // cout << "in a3: " << endl;
    // for(auto x : a3){
    //     cout << x.f << " " << x.s << endl;
    // }
    while(true){
        // cout << sz(a1) << " " << sz(a3) << " " << sz(b2) << " " << sz(b3) << " " << sz(c1) << " " << sz(c2) << endl;
        auto sa3 = a ? a3.begin() : a3.end(), 
        sa1 = a ? a1.begin() : a1.end(), 
        sb2 = b ? b2.begin() : b2.end(), 
        lb3 = b ? prev(b3.end()) : b3.end(), 
        lc1 = c ? prev(c1.end()) : c1.end(), 
        lc2 = c ? prev(c2.end()) : c2.end();
        // cout << "in a1: " << endl;
        //     for(auto x : a1){
        //         cout << x.f << "," << x.s << " and ";
        //     }
        //     cout << endl;
        //     cout << "in a3: " << endl;
        //     for(auto x : a3){
        //         cout << x.f << "," << x.s << " and ";
        //     }
        //     cout << endl;
        if(a && b && cmp3()(*sa3, *lb3)){
            // cout << "swap a/b" << endl;
            pl ap = *sa3, bp = *lb3;
            // cout << "swapped " << ap.f << "," << ap.s << " from a, " << bp.f << "," << bp.s << " from b" << endl;
            a3.erase(a3.find(ap)), a1.erase(a1.find(ap));
            b3.erase(b3.find(bp)), b2.erase(b2.find(bp));
            b3.insert(ap), b2.insert(ap);
            a3.insert(bp), a1.insert(bp);
            continue;
        }
        if(a && c && cmp1()(*sa1, *lc1)){
            // cout << "swap a/c" << endl;
            pl ap = *sa1, cp = *lc1;
            // cout << "end swapping a/c" << endl;
            // cout << "target: " << ap.f << " " << ap.s << endl;
            // cout << a1.count(ap) << " " << a3.count(ap) << endl;
            a1.erase(a1.find(ap));
            // cout << "removed sa1" << endl;
            a3.erase(a3.find(ap));
            // cout << "end swapping a/c" << endl;
            c1.erase(lc1), c2.erase(c2.find(cp));
            // cout << "end swapping a/c" << endl;
            c1.insert(ap), c2.insert(ap);
            // cout << "end swapping a/c" << endl;
            a1.insert(cp), a3.insert(cp);
            // cout << "end swapping a/c" << endl;
            continue;
        }
        if(b && c && cmp2()(*sb2, *lc2)){
            // cout << "swap b/c" << endl;
            auto bp = *sb2, cp = *lc2;
            b2.erase(b2.find(bp)), b3.erase(b3.find(bp));
            c2.erase(c2.find(cp)), c1.erase(c1.find(cp));
            c1.insert(bp), c2.insert(bp);
            b2.insert(cp), b3.insert(cp);
            continue;
        }
        if(a && b && c){
            // cout << "swap a->b->c" << endl;
            auto ap = *sa3, bp = *sb2, cp = *lc1;
            if(ap.s - ap.f - bp.s + cp.f > 0){
                a3.erase(a3.find(ap)), a1.erase(a1.find(ap));
                b2.erase(b2.find(bp)), b3.erase(b3.find(bp));
                c1.erase(c1.find(cp)), c2.erase(c2.find(cp));
                a1.insert(cp), a3.insert(cp);
                b2.insert(ap), b3.insert(ap);
                c1.insert(bp), c2.insert(bp);
                continue;
            }
        }
        if(a && b && c){
            // cout << "swap a->c->b" << endl;
            auto ap = *sa1, bp = *lb3, cp = *lc2;
            if(-ap.f + cp.s + bp.f - bp.s > 0){
                a1.erase(a1.find(ap)), a3.erase(a3.find(ap));
                b3.erase(b3.find(bp)), b2.erase(b2.find(bp));
                c2.erase(c2.find(cp)), c1.erase(c1.find(cp));
                a1.insert(cp), a3.insert(cp);
                b2.insert(ap), b3.insert(ap);
                c1.insert(bp), c2.insert(bp);
                continue;
            }
        }
        break;
    }
    // cout << "got here" << endl;
    ll score = 0;
    for(auto x : a1){
        score += x.f;
    }
    for(auto x : b2) score += x.s;
    cout << score << "\n";
    

    
    return 0;
}
