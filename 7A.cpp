//
// Created by 91342 on 2018/11/15.
//

#include <iostream>
#include <string>
using namespace std;


int n,m;
string base[110];
int map[110][110] = {};

void floyd(){
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j){
                if(map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
            }
}

int main(){
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> base[i];
    }
    m = base[0].size();

    for(int i = 0; i < n; ++i){
        map[i][i] = 0;
        for(int j = i + 1; j < n; ++j){
            int diff = 0;
            for(int k = 0; k < m; ++k)
                if(base[i][k] != base[j][k]) diff ++;
            map[i][j] = map[j][i] = diff * diff;
        }
    }

    floyd();

    int ans = 1e9;
    for(int i = 0; i < n; ++i){
        int maxtime = 0;
        for(int j = 0; j < n; ++j)
            if(i != j) maxtime = max(map[i][j],maxtime);
        ans = min(ans,maxtime);
    }

    cout << ans << endl;
    return 0;

}