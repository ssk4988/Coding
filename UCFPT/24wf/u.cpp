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

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

tuple<int, vi, vi> solve6(int s, int c){
    if(!((c / 2 * 2) % 4 == 2 && s >= 2)) return {0, {}, {}};
    c -= 6;
    s -= 2;
    int ans = 8;
    c = c / 4;
    s = s / 2;
    int usec4 = c / 2;
    vi ss(2);
    vi cc(2);
    cc[0] = cc[1] = usec4;
    // cc[0] = cc[1] = usec2 / 2;
    c -= usec4 * 2;
    // c2 -= usec2;
    if(c && s){
        s--;
        c--;
        ss[0] += 2;
        cc[1]++;
    }
    ss[0] += s;
    ss[1] += s;
    ans += 4 * (cc[0] + cc[1]);
    ans += ss[0] + ss[1];
    s = 0;
    return {ans, ss, cc};
}

tuple<int, vi, vi> solve4(int s, int c){
    c -= 4;
    int ans = 4;
    c = c / 4;
    s = s / 2;
    int usec4 = c / 2;
    vi ss(2);
    vi cc(2);
    cc[0] = cc[1] = usec4;
    // cc[0] = cc[1] = usec2 / 2;
    c -= usec4 * 2;
    // c2 -= usec2;
    if(c && s){
        s--;
        c--;
        ss[0] += 2;
        cc[1]++;
    }
    ss[0] += s;
    ss[1] += s;
    ans += 4 * (cc[0] + cc[1]);
    ans += ss[0] + ss[1];
    s = 0;
    return {ans, ss, cc};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int s, c; cin >> s >> c;
    auto ans4 = solve4(s, c), ans6 = solve6(s, c);
    vector<string> ends(2, "LL");
    vi ss, cc; int ans;
    if(get<0>(ans4) > get<0>(ans6)){
        tie(ans, ss, cc) = ans4;
    }else{
        ends[0] = "SLSLLR";
        tie(ans, ss, cc) = ans6;
    }
    
    rep(i, 0, 2){
        rep(j, 0, ss[i]){
            cout << "S";
        }
        rep(j, 0, cc[i]){
            cout << "RLLR";
        }
        cout << ends[i];
    }
    cout << "\n";


    
    return 0;
}
