//radio.cpp
//Jacob Steinebronn

#include <bits/stdc++.h>
#define newl '\n'

using namespace std;

int main(){
    int nq;
    cin >> nq;

    for(int dayn=1;dayn<=nq;dayn++){
        cout << "Day #" << dayn << ":\n";
        int n, p, s;
        cin >> n >> p >> s;

        //Store the radio stations
        vector<double> radio(n, 0);

        //Store the indices of the presets
        vector<int> presets(p, -1);


        //Fill the radio[] array with the radio stations
        for(int i=0;i<n;i++)
            cin >> radio[i];
        
        
        //Parse the presets, and fill the presets array with the indices of these stations
        for(int i=0;i<p;i++){
            double pre;
            cin >> pre;
            for(int j=0;j<n;j++){
                if(radio[j]==pre){
                    presets[i]=j;
                    break;
                }
            }
        }

        for(int i=0;i<s;i++){
            double start, finish;
            cin >> start >> finish;
            int idxStart,idxEnd;

            //Find which index we're starting and ending at
            for(int i=0;i<n;i++){
                if(radio[i]==start)
                    idxStart=i;
                else if(radio[i]==finish)
                    idxEnd = i;
            }

            //Without presets, you can either go directly from start to end
            //Or wrap around the end, so take the shorter of these two
            int ans=min(abs(idxStart-idxEnd),n-abs(idxStart-idxEnd));
            
            //For each idx we can get to from taking a preset...
            for(int idx:presets){
                //min ans with 1 + the dist formula from above (the 1 + since it takes one button press to get to the preset)
                ans=min(ans,1+min(abs(idx-idxEnd),n-abs(idx-idxEnd)));
            }

            cout << ans << newl;
        }
        cout << newl;
    }
}
