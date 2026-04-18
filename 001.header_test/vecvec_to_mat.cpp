#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    int N;cin>>N;
    vector<double>v;v.resize(N);
    for(int i=0;i<N;i++)cin>>v[i];
    int M;cin>>M;
    vector<double>vv;vv.resize(M);
    for(int i=0;i<M;i++)cin>>vv[i];
    vector<vector<double>> tmp;
    tmp=vecvec_to_mat(v,vv);
    print_2D(tmp);
}