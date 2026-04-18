#include<sungso376_LA.hpp>
#include<sungso376_debbuging.hpp>
#include<vector>
#include<iostream>
using namespace std;
int main(void){
    int N;cin>>N;
    vector<double>v;v.resize(N);
    for(int i=0;i<N;i++)cin>>v[i];
    vector<vector<double>> tmp;
    tmp=vec_to_mat(v);
    print_2D(tmp);
}