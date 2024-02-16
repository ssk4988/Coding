#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long int;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ld = long double;
using pdd = pair<ld, ld>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vdd = vector<pdd>;

#define f first
#define s second

ld fullcover(ld a, ld b, ld c, ld d){
    if(a < c){
        swap(a, c), swap(b, d);
    }
    return (b * b * b - a * a * a) / 3 - (c + d) / 2 * (b * b - a * a) + (c * c + d * d) / 2 * (b - a);
}

ld nocover(ld a, ld b, ld c, ld d){
    if(a > c){
        swap(a, c), swap(b, d); // not necessary
    }
    return ((d * d - c * c) * (b - a) - (d - c) * (b * b - a * a)) / 2;
}

ld partcover(ld a, ld b, ld c, ld d){
    if(a > c){
        swap(a, c), swap(b, d);
    }
    return nocover(a, c, c, d) + fullcover(c, b, c, d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // cout << fullcover(1, 4, 2, 3) << " " << fullcover(11, 14, 12, 13) << endl;
    // cout << partcover(1, 5, 4, 7) << " " << partcover(11, 15, 14, 17) << endl;
    // cout << nocover(1, 5, 8, 10) << " " << nocover(11, 15, 18, 20) << endl;
    int n, m; cin >> n >> m;
    vll along(n), blong(m);
    vdd asd(n), bsd(m);
    ll lena = 0, lenb = 0;
    rep(i, 0, n){
        cin >> along[i].f >> along[i].s;
        lena += along[i].s - along[i].f;
        asd[i] = along[i];
    }
    rep(i, 0, m){
        cin >> blong[i].f >> blong[i].s;
        lenb += blong[i].s - blong[i].f;
        bsd[i] = blong[i];
    }
    cout << fixed << setprecision(10);
    sort(all(asd)); sort(all(bsd));
    sort(all(along)); sort(all(blong));
    if(lena == 0 || lenb == 0){
        if(lena == 0 && lenb == 0){
            ld ans = 0;
            int p1 = -1;
            ld left1 = 0;
            rep(i, 0, n){
                auto [c, d] = asd[i];
                while(p1 + 1 < m && bsd[p1 + 1].f <= c){
                    p1++; auto [a, b] = bsd[p1];
                    left1 += -a;
                }
                ans += c * (p1 + 1) + left1;
            }
            p1 = m;
            left1 = 0;
            for(int i = n - 1; i >= 0; i--){
                auto [c, d] = asd[i];
                while(p1 - 1 >= 0 && bsd[p1 - 1].f >= c){
                    p1--; auto[a, b] = bsd[p1];
                    left1 += a;
                }
                ans += -c * (m - p1) + left1;
            }
            // ans /= 2; // very important
            ans /= m; ans /= n;
            cout << ans << "\n";
            return 0;
        }
        else if(lenb == 0){
            swap(lenb, lena);
            swap(n, m);
            swap(along, blong);
            swap(asd, bsd);
        }
        // lena = 0

        ld ans = 0;
        int p1 = -1;
        ld left1 = 0, left2 = 0;
        rep(i, 0, n){
            auto [c, d] = asd[i];
            while(p1 + 1 < m && bsd[p1 + 1].s <= c){
                p1++; auto [a, b] = bsd[p1];
                left1 += 2 * (b - a);
                left2 += a * a - b * b;
            }
            ans += left1 * c + left2;
            if(p1 + 1 < m && bsd[p1 + 1].s > d && bsd[p1 + 1].f < c){
                auto [a, b] = bsd[p1 + 1];
                ans += ((c - a) * (c - a) + (b - c) * (b - c));
            }
        }
        p1 = m;
        left1 = 0, left2 = 0;
        for(int i = n - 1; i >= 0; i--){
            auto [c, d] = asd[i];
            while(p1 - 1 >= 0 && bsd[p1 - 1].f >= d){
                p1--; auto[a, b] = bsd[p1];
                left1 += 2 * (a - b);
                left2 += b * b - a * a;
            }
            ans += left1 * c + left2;
        }
        ans /= 2; // very important
        ans /= n; ans /= lenb;
        cout << ans << "\n";

        return 0;
    }
    int p = -1;
    ld left1 = 0, left2 = 0;
    ld ans = 0;
    rep(i, 0, n){
        auto [c, d] = asd[i];
        // cout << "try interval " << i << endl;
        // add all intervals completely to the left
        while(p + 1 < m && bsd[p + 1].s <= c){
            p++;
            // no cover from left
            auto [a, b] = bsd[p];
            left1 += b - a;
            left2 += b * b - a * a;
        }
        ans += (d * d - c * c) * left1 / 2 + (d - c) * left2 / 2;
        while(p + 1 < m && bsd[p + 1].s <= d && bsd[p + 1].f <= c){
            // partial cover from left
            p++;
            auto [a, b] = bsd[p];
            left1 += b - a;
            left2 += b * b - a * a;
            ans += partcover(a, b, c, d);
        }
        while(p + 1 < m && bsd[p + 1].s <= d && bsd[p + 1].f >= c){
            // i full cover
            p++;
            auto [a, b] = bsd[p];
            left1 += b - a;
            left2 += b * b - a * a;
            ans += fullcover(a, b, c, d);
        }
        if(p + 1 < m && bsd[p + 1].s >= d && bsd[p + 1].f <= d && bsd[p + 1].f >= c){
            // partial cover from right
            auto [a, b] = bsd[p + 1];
            ans += partcover(c, d, a, b);
        }
        if(p + 1 < m && bsd[p + 1].s >= d && bsd[p + 1].f <= c){
            // full cover me
            auto [a, b] = bsd[p + 1];
            ans += fullcover(c, d, a, b);
        }
    }
    p = m;
    ld right1 = 0, right2 = 0;
    for(int i = n - 1; i >= 0; i--){
        auto [a, b] = asd[i];
        while(p - 1 >= 0 && bsd[p - 1].f >= b){
            // no cover from right
            p--;
            auto [c, d] = bsd[p];
            right1 += d - c;
            right2 += d * d - c * c;
        }
        ans +=((b - a) * right2 + (b * b - a * a) * right1) / 2;
    }
    ans /= lena, ans /= lenb;
    cout << ans << "\n";


    return 0;
}