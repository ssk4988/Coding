#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t, n; cin >> t >> n;
    rep(cn, 0, t){
        ll k; cin >> k;
        ll score = 1;
        pi place = {1, 1};
        if(k % 2 == 1){
            cout << "-1\n";
            continue;
        }
        int moves = 0;
        auto inbounds = [&]()->bool{
            return place.f >= 1 && place.f <= n && place.s >= 1 && place.s <= 100;
        };
        auto up = [&]()->void{
            assert(score % 2 == 0);
            score /= 2;
            cout << "U";
            place.f--;
            moves++;
            assert(inbounds());
        };
        auto down = [&]()->void{
            score *= 2;
            assert(score <= 2 * k);
            cout << "D";
            place.f++;
            moves++;
            assert(inbounds());
        };
        auto left = [&]()->void{
            assert(score >= 2);
            score -= 2;
            cout << "L";
            place.s--;
            moves++;
            assert(inbounds());
        };
        auto right = [&]()->void{
            score += 2;
            assert(score <= 2 * k);
            cout << "R";
            place.s++;
            moves++;
            assert(inbounds());
        };
        down();
        auto rightsafe = [&]()->void{
            right();
            up();
            left();
            down();
            right();
        };
        rep(i, 0, 98){
            rightsafe();
        }
        right();
        up();
        left();
        down();
        vl rows(101);
        rows[100] = k;
        int row2 = 100;
        for(row2 = 100; row2 >= 0 && rows[row2] > 2; row2--){
            rows[row2 - 1] = (rows[row2] + 1) / 2;
        }
        while(place.f < row2){
            down();
        }
        right();
        if(score == k && place.f == 100 && place.s == 100){
            cout << "\n";
            continue;
        }
        auto dec1 = [&]()->void{
            left();
            down();
            right();
            up();
        };
        rep(i, row2, 99){
            down();
            while(score > rows[i + 1]){
                dec1();
            }
        }
        // location 99, 100
        down();
        cout << "\n";
        // cout << score << "\n";
        assert(score == k && place.f == 100 && place.s == 100);
        // rep(i, 0, 4){
        //     down();
        // }
        // rep(i, )
    }
}
