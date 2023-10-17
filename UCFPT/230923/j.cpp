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

struct Card{
    int count, color, fill, shape;
    Card(string &str){
        count = str[0] - '1';
        if(str[1] == 'G') color = 0;
        if(str[1] == 'B') color = 1;
        if(str[1] == 'R') color = 2;
        if(str[2] == 'E') fill = 0;
        if(str[2] == 'S') fill = 1;
        if(str[2] == 'F') fill = 2;
        if(str[3] == 'A') shape = 0;
        if(str[3] == 'D') shape = 1;
        if(str[3] == 'O') shape = 2;
    }
};

bool formset(Card &c1, Card &c2, Card &c3){
    int count = 0, color = 0, fill = 0, shape = 0;
    for(Card c : {c1, c2, c3}){
        count += c.count;
        color += c.color;
        fill += c.fill;
        shape += c.shape;
    }
    count %= 3;
    color %= 3;
    fill %= 3;
    shape %= 3;
    return !count && !color && !fill && !shape;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<pair<Card, Card>> cards;
    rep(i, 0, n){
        string str1, str2; cin >> str1 >> str2;
        cards.emplace_back(Card(str1), Card(str2));
    }
    int ans = 0;
    rep(i, 0, n){
        rep(j, 0, i){
            rep(k, 0, j){
                auto x = vi{i, j, k};
                bool works = false;
                rep(b, 0, 1 << 3){
                    rep(l, 0, 3){
                        if((b >> l) & 1) swap(cards[x[l]].f, cards[x[l]].s);
                    }
                    works = works || formset(cards[i].f, cards[j].f, cards[k].f) && formset(cards[i].s, cards[j].s, cards[k].s);
                    // if(works){
                    //     ans++;
                    //     cout << i << " " << j << " " << k << " " << b << nL;
                    // }
                    rep(l, 0, 3){
                        if((b >> l) & 1) swap(cards[x[l]].f, cards[x[l]].s);
                    }
                }
                ans += works;
            }
        }
    }
    cout << ans << nL;
    
    return 0;
}
