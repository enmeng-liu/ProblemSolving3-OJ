//
// Created by 91342 on 2018/11/27.
//

#include <iostream>
#include <vector>
#define N 1010
using namespace std;

int n;
bool map[N][N] = {};
vector <int> path;

void hamilton(){
    path.push_back(1);
    for(int i = 2; i <= n; ++i){
        bool flag = false;
        for(int j = 0; j < path.size() - 1; ++j){
            if(map[path[j]][i] && map[i][path[j + 1]]){
                path.insert(path.begin() + j + 1, i);
                flag = true;
                break;
            }
        }
        if(flag) continue;
        if(map[path.back()][i]) path.push_back(i);
        else path.insert(path.begin(), i);
    }
}


int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cin >> map[i][j];

    hamilton();

    cout << n << endl;
    for(int i = 0; i < path.size(); ++i) cout << path[i] << " ";
    cout << "-1\n" ;
}