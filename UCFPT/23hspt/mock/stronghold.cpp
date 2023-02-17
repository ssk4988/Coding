#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long double ld;

ld eps = 1e-10;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int x1, x2, y1, y2, a1, a2;
    cin >> x1 >> y1 >> a1 >> x2 >> y2 >> a2;
    ld pi = acosl(-1);
    a1 = ((90 - a1) % 360 + 360) % 360;
    a2 = ((90 - a2) % 360 + 360) % 360;

    if(a1 == 90 || a1 == 270 || a2 == 90 || a2 == 270){
        ld newx = (a1 == 90 || a1 == 270) ? x1 : x2, newy = -1;
        ld s1, s2, b1, b2, la2, la1;
        if(a1 == 90 || a1 == 270){
            la2 = a2 * pi / 180;
            s2 = tanl(la2);
            b2 = y2 - s2 * x2;
            newy = newx * s2 + b2;
        }
        else{
            la1 = a1 * pi / 180;
            s1 = tanl(la1);
            b1 = y1 - s1 * x1;
            newy = newx * s1 + b1;
        }
        ld scalethis = 0, scalethat;
        ld dythis = (a1 == 90 || a1 == 270) ? (newy - y1) : (newy - y2);
        ld dx = (a1 == 90 || a1 == 270) ? (newx - x2) : (newx - x1);
        ld dirythis = (a1 == 90 || a1 == 270) ? (a1 == 90 ? 1 : -1) : (a2 == 90 ? 1 : -1);
        ld dirx = (a1 == 90 || a1 == 270) ? cosl(la2): cosl(la1);
        
        scalethis = dythis / dirythis;
        scalethat = dx / dirx;
        if(abs(scalethis) < eps || scalethis < eps || abs(scalethat) < eps || scalethat < eps){
            cout << "-1\n";
        }
        else{
            cout << newx << " " << newy << "\n";
        }
        
    }
    else{
        ld la1 = a1 * pi / 180, la2 = a2 * pi / 180;
        ld s1 = tanl(la1), s2 = tanl(la2);
        ld b1 = y1 - s1 * x1, b2 = y2 - s2 * x2;
        ld newx = (b2 - b1) / (s1 - s2);
        ld newy = s1*newx + b1;
        // cout << newx << " " << newy << "\n";
        ld vx1 = cosl(la1), vy1 = sinl(la1), vx2 = cosl(la2), vy2 = sinl(la2);
        ld dx1 = newx - x1, dy1 = newy - y1, dx2 = newx - x2, dy2 = newy - y2;
        ld scale1 = 0, scale2 = 0;
        if(abs(dy1) < eps){
            scale1 = dx1 / vx1;
            scale2 = dx2 / vx2;
        }
        else{
            scale1 = dy1 / vy1;
            scale2 = dy2 / vy2;
        }
        if(abs(scale1) < eps || scale1 < eps || abs(scale2) < eps || scale2 < eps){
            cout << "-1\n";
        }
        else{
            cout << newx << " " << newy << "\n";
        }
    }


    
}