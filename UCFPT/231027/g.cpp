#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vll = vector<ll>;

struct P{
    int x, y;
    explicit P(int x = 0, int y = 0): x(x), y(y){}
    bool operator<(P p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator>(P p) const {
        return tie(x, y) > tie(p.x, p.y);
    }
    bool operator==(P p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
};

P transform(int x, int y){
    return P(x + y, x - y);
}
#define f first
#define s second
using R = pair<P, P>;

vector<R> segmentize(int x, int y, int d){
    if(d == 0) return {{transform(x, y), transform(x, y)}};
    vector<R> r;
    r.push_back({transform(x+d, y), transform(x, y+d)});
    r.push_back({transform(x, y+d), transform(x-d, y)});
    r.push_back({transform(x-d, y), transform(x, y-d)});
    r.push_back({transform(x, y-d), transform(x+d, y)});
    for(auto &p : r){
        if(p.f > p.s) swap(p.f, p.s);
        // assert(!(p.f > p.s));
    }
    return r;
}

int type(R &r){
    if(r.f.x != r.s.x) return 1; // horizontal
    if(r.f.y != r.s.y) return 2; // vertical
    return 0;
}

P badp(1e9, 1e9);
R badr{badp, badp};

R intersect(R r1, R r2){
    int t1 = type(r1), t2 = type(r2);
    if(t1 == 0){
        bool inside = r2.f.x <= r1.f.x && r1.f.x <= r2.s.x && r2.f.y <= r1.f.y && r1.f.y <= r2.s.y;
        if(!inside) return badr;
        return {r1.f, r1.f};
    }
    if(t2 == 0){
        bool inside = r1.f.x <= r2.f.x && r2.f.x <= r1.s.x && r1.f.y <= r2.f.y && r2.f.y <= r1.s.y;
        if(!inside) return badr;
        return {r2.f, r2.f};
    }
    if(t1 == t2){
        if(t1 == 1 && r1.f.y != r2.f.y || t1 == 2 && r1.f.x != r2.f.x) return badr;
        // if(r1.f.x != r2.f.x && r1.f.y != r2.f.y) return badr;
        P s = max(r1.f, r2.f), e = min(r1.s, r2.s);
        if(e < s) return badr;
        // cout << s.x << " " << s.y << " | " << e.x << " " << e.y << "\n";
        return {s, e};
    }
    // t1 != t2
    if(t1 == 2) swap(r1, r2);
    // r1 is horizontal
    bool good = r1.f.x <= r2.f.x && r2.f.x <= r1.s.x && r2.f.y <= r1.f.y && r1.f.y <= r2.s.y;
    if(!good) return badr;
    P intp(r2.f.x, r1.f.y);
    return {intp, intp};
}

inline bool valid(P p){
    return (p.x + p.y) % 2 == 0 && (p.x - p.y) % 2 == 0;
}

P invert(P p){
    return P((p.x + p.y)/2, (p.x - p.y)/2);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int x, y, d; cin >> x >> y >> d;
    vector<R> ints = segmentize(x, y, d);
    rep(i, 0, n-1){
        cin >> x >> y >> d;
        vector<R> sq = segmentize(x, y, d);
        vector<R> newints;
        for(R &r : ints){
            for(R &r1 : sq){
                R res = intersect(r, r1);
                if(res == badr) continue;
                if(type(res) == 0){
                    bool found = false;
                    for(R &nr : newints){
                        if(nr == res){
                            found = true;
                            break;
                        }
                    }
                    if(!found) newints.emplace_back(res);
                }
                else{
                    newints.emplace_back(res);
                }
            }
        }
        ints = newints;
    }
    // cout << sz(ints) << "\n";
    set<P> ans;
    for(auto &r : ints){
        auto &[p1, p2] = r;

        // cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";
        if(type(r) == 0){
            if(valid(r.f)){
                ans.insert(invert(r.f));
            }
        }
        else if(type(r) == 1){
            while(r.f.x <= r.s.x){
                if(valid(r.f)){
                    ans.insert(invert(r.f));
                }
                r.f.x++;
            }
        }
        else{
            while(r.f.y <= r.s.y){
                if(valid(r.f)){
                    ans.insert(invert(r.f));
                }
                r.f.y++;
            }
        }
    }
    for(auto [x, y] : ans){
        cout << x << " " << y << "\n";
    }
    return 0;
}