//Chocolate.cpp
//Jacob Steinebronn

#include <bits/stdc++.h>
#define newl '\n'

using namespace std;

int main(){
    int nq;
    cin >> nq;

    while(nq--){
        int n, m;
        cin >> n >> m;

        //Keep track for each possible starting point, how many ranges start at this point
        vector<int> numStartHere(n+2,0);

        //Keep track of each ending point
        vector<int> ends(m,0);

        //Parse input
        for(int i=0;i<m;i++){
            int l, r;
            cin >> l >> r;
            numStartHere[l]++;
            ends[i]=r;
        }

        //Assume none of the ranges can be combined together
        int ans = m;
        for(int end:ends){
            //If a range starts right after this current one ends, we can merge them, so decrement ans since 2 ranges became one
            if(numStartHere[end+1]){
                numStartHere[end+1]--;
                ans--;
            }
        }
        cout << ans << newl;

    }
}
