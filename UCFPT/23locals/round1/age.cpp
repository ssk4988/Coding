#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int a1, a2, a3; cin >> a1 >> a2 >> a3;
    bool works = false;
    for(int i = 1; i <= 150; i++){
        for(int j = 1; j <= 150; j++){
            if(i * a2 + j * a3 == a1) works = true;
        }
    }
    cout << works << "\n";
}
