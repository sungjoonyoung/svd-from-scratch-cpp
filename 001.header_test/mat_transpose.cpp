#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    int N,M;cin>>N>>M;
    vector<vector<double>>v;v.resize(N);
    for(int i=0;i<N;i++)for(int j=0;j<M;j++){
        double in;cin>>in;
        v[i].push_back(in);
    }
    print_2D(v);
    vector<vector<double>>tmp=mat_transpose(v);
    print_2D(tmp);
}